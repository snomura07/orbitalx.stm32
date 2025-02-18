#include "imu.h"
#include "icm_20648.h"

Imu::Imu(SPI_HandleTypeDef &hspi_, uint8_t deviceAddress)
    : hspi(&hspi_), devAddr(deviceAddress << 1) {}
Imu::~Imu(){}

bool Imu::init() {
    // スリープ解除 一度送信しただけじゃ解除されないので複数回送信
    uint8_t addr = 0x01;
    for(int i=0; i<5; i++){
        writeRegister(ICM20648::PWR_MGMT_1, &addr, 1);
        HAL_Delay(100);
    }

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

void Imu::update() {
    readAll();
}

void Imu::readAll() {
    uint8_t rawData[12] = {0};
    readRegister(ICM20648::ACCEL_XOUT_H, rawData, 12);
    accelRaw.x = (int16_t)((rawData[0]  << 8) | rawData[1]);
    accelRaw.y = (int16_t)((rawData[2]  << 8) | rawData[3]);
    accelRaw.z = (int16_t)((rawData[4]  << 8) | rawData[5]);
    gyroRaw.x  = (int16_t)((rawData[6]  << 8) | rawData[7]);
    gyroRaw.y  = (int16_t)((rawData[8]  << 8) | rawData[9]);
    gyroRaw.z  = (int16_t)((rawData[10] << 8) | rawData[11]);
}

bool Imu::writeRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    uint8_t txBuffer[size + 1];
    txBuffer[0] = reg & 0x7F;  // 最上位ビットをクリア (書き込み)
    memcpy(&txBuffer[1], data, size);

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    bool status = (HAL_SPI_Transmit(hspi, txBuffer, size + 1, HAL_MAX_DELAY) == HAL_OK);
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    return status;
}

bool Imu::readRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    uint8_t txBuffer = reg | 0x80;  // 最上位ビットをセット (読み込み)

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    bool status = (HAL_SPI_Transmit(hspi, &txBuffer, 1, HAL_MAX_DELAY) == HAL_OK &&
                   HAL_SPI_Receive(hspi, data, size, HAL_MAX_DELAY) == HAL_OK);
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    return status;
}

void Imu::dump(){
    sendMessage("accel[LSB]: ");
    sendInt(accelRaw.x);
    sendMessage(", ");
    sendInt(accelRaw.y);
    sendMessage(", ");
    sendInt(accelRaw.z);
    sendMessage(", ");

    sendMessage("gyro[LSB] : ");
    sendInt(gyroRaw.x);
    sendMessage(", ");
    sendInt(gyroRaw.y);
    sendMessage(", ");
    sendInt(gyroRaw.z);
    sendMessage("\r\n");
}

char* Imu::getChipName() {
    return ICM20648::CHIP_NAME;
}
