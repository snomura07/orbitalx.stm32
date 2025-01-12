#include "imu.h"
#include "icm_20648.h"

Imu::Imu(I2C_HandleTypeDef &hi2c_, uint8_t deviceAddress)
    : hi2c(&hi2c_), devAddr(deviceAddress << 1) {}
Imu::~Imu(){}

bool Imu::init() {
    uint8_t whoAmI = 0;

    // スリープ解除
    writeRegister(ICM20648::PWR_MGMT_1, 0x00);
    HAL_Delay(10);

    // 加速度: ±16g
    writeRegister(ICM20648::ACCEL_CONFIG, 0x18);    // ±16g設定
    writeRegister(ICM20648::ACCEL_CONFIG_2, 0x03); // 加速度DLPF設定: 45Hz

    // ジャイロ: ±2,000°/s
    writeRegister(ICM20648::GYRO_CONFIG_1, 0x1B); // ジャイロFSR設定: ±2,000°/s, DLPF=3

    // サンプリングレート設定（1kHz ODR）
    writeRegister(ICM20648::SMPLRT_DIV_1, 0x00); // 上位バイト: 分周なし
    writeRegister(ICM20648::SMPLRT_DIV_2, 0x00); // 下位バイト: 分周なし

    sendMessage("test1\r\n");
    return true;
}

uint8_t Imu::whoAmI() {
    uint8_t whoAmI = 0;
    if (!readRegister(ICM20648::WHO_AM_I, &whoAmI, 1)) {
        return 0xFF;
    }
    return whoAmI;
}

bool Imu::readAccel(float& ax, float& ay, float& az) {
    uint8_t rawData[6] = {0};
    readRegister(ICM20648::ACCEL_XOUT_H, rawData, 6);
    int16_t rawAx = (rawData[0] << 8) | rawData[1];
    int16_t rawAy = (rawData[2] << 8) | rawData[3];
    int16_t rawAz = (rawData[4] << 8) | rawData[5];

    ax = rawAx * ICM20648::ACCEL_SCALE;
    ay = rawAy * ICM20648::ACCEL_SCALE;
    az = rawAz * ICM20648::ACCEL_SCALE;

    return true;
}

bool Imu::readGyro(float& gx, float& gy, float& gz) {
    uint8_t rawData[6] = {0};
    readRegister(ICM20648::GYRO_XOUT_H, rawData, 6);
    int16_t rawGx = (rawData[0] << 8) | rawData[1];
    int16_t rawGy = (rawData[2] << 8) | rawData[3];
    int16_t rawGz = (rawData[4] << 8) | rawData[5];

    gx = rawGx * ICM20648::GYRO_SCALE;
    gy = rawGy * ICM20648::GYRO_SCALE;
    gz = rawGz * ICM20648::GYRO_SCALE;

    return true;
}

bool Imu::writeRegister(uint8_t reg, uint8_t data) {
    auto res = HAL_I2C_Mem_Write(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
    sendMessage("res: ");
    sendInt(res);
    sendMessage("\r\n");
    return true;

    // return HAL_I2C_Mem_Write(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100) == HAL_OK;
}

bool Imu::readRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    return HAL_I2C_Mem_Read(hi2c, devAddr, reg, I2C_MEMADD_SIZE_8BIT, data, size, HAL_MAX_DELAY) == HAL_OK;
}
