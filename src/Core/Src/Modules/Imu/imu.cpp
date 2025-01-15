#include "imu.h"
#include "icm_20648.h"

Imu::Imu(I2C_HandleTypeDef &hi2c_, uint8_t deviceAddress)
    : hi2c(&hi2c_), devAddr(deviceAddress << 1) {}
Imu::~Imu(){}

bool Imu::init() {
    // スリープ解除
    uint8_t addr = 0x01;
    writeRegister(ICM20648::PWR_MGMT_1, &addr, 1);
    HAL_Delay(100);

    // 加速度: ±16g
    addr = 0x18;
    writeRegister(ICM20648::ACCEL_CONFIG, &addr, 1);
    HAL_Delay(100);

    // ジャイロ: ±2,000°/s
    addr = 0x18;
    writeRegister(ICM20648::GYRO_CONFIG, &addr, 1);
    HAL_Delay(100);

    return true;
}

uint8_t Imu::whoAmI() {
    uint8_t whoAmI = 0;
    if (!readRegister(ICM20648::WHO_AM_I, &whoAmI, 1)) {
        return 0xFF;
    }
    return whoAmI;
}

void Imu::readAll() {
    uint8_t rawData[12] = {0};
    readRegister(ICM20648::ACCEL_XOUT_H, rawData, 12);
    accel.x = (int16_t)((rawData[0]  << 8) | rawData[1]);
    accel.y = (int16_t)((rawData[2]  << 8) | rawData[3]);
    accel.z = (int16_t)((rawData[4]  << 8) | rawData[5]);
    gyro.x  = (int16_t)((rawData[6]  << 8) | rawData[7]);
    gyro.y  = (int16_t)((rawData[8]  << 8) | rawData[9]);
    gyro.z  = (int16_t)((rawData[10] << 8) | rawData[11]);
}

bool Imu::writeRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    return HAL_I2C_Mem_Write(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, data, size, 500) == HAL_OK;
}

bool Imu::readRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    return HAL_I2C_Mem_Read(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY) == HAL_OK;
}

void Imu::out(){
    sendMessage("accel[LSB]: ");
    sendInt(accel.x);
    sendMessage(", ");
    sendInt(accel.y);
    sendMessage(", ");
    sendInt(accel.z);
    sendMessage(", ");

    sendMessage("gyro[LSB] : ");
    sendInt(gyro.x);
    sendMessage(", ");
    sendInt(gyro.y);
    sendMessage(", ");
    sendInt(gyro.z);
    sendMessage("\r\n");
}
