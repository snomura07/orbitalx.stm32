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
    writeRegister(ICM20648::ACCEL_CONFIG, &addr, 1); // ±16g設定
    HAL_Delay(100);

    // ジャイロ: ±2,000°/s
    addr = 0x18;
    writeRegister(ICM20648::GYRO_CONFIG, &addr, 1); // FS_SEL=3 (±2,000°/s), DLPF=0 (無効)
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
    accelI.x = (int16_t)((rawData[0]  << 8) | rawData[1]);
    accelI.y = (int16_t)((rawData[2]  << 8) | rawData[3]);
    accelI.z = (int16_t)((rawData[4]  << 8) | rawData[5]);
    gyroI.x  = (int16_t)((rawData[6]  << 8) | rawData[7]);
    gyroI.y  = (int16_t)((rawData[8]  << 8) | rawData[9]);
    gyroI.z  = (int16_t)((rawData[10] << 8) | rawData[11]);

    accelF.x = (float)accelI.x / ICM20648::ACCEL_SCALE * 9.80665f;
    accelF.y = (float)accelI.y / ICM20648::ACCEL_SCALE * 9.80665f;
    accelF.z = (float)accelI.z / ICM20648::ACCEL_SCALE * 9.80665f;
    gyroF.x  = (float)gyroI.x  / ICM20648::GYRO_SCALE;
    gyroF.y  = (float)gyroI.y  / ICM20648::GYRO_SCALE;
    gyroF.z  = (float)gyroI.z  / ICM20648::GYRO_SCALE;
}

bool Imu::writeRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    return HAL_I2C_Mem_Write(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, data, size, 500) == HAL_OK;
}

bool Imu::readRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    return HAL_I2C_Mem_Read(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY) == HAL_OK;
}

void Imu::out(){
    sendMessage("accel[m/ss]: ");
    sendFloat(accelF.x);
    sendMessage(", ");
    sendFloat(accelF.y);
    sendMessage(", ");
    sendFloat(accelF.z);
    sendMessage(", ");

    sendMessage("gyro[dps] : ");
    sendFloat(gyroF.x);
    sendMessage(", ");
    sendFloat(gyroF.y);
    sendMessage(", ");
    sendFloat(gyroF.z);
    sendMessage("\r\n");
}
