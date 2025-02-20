#include "imu.h"
#include "icm_20648.h"
Imu* Imu::instance;

Imu::Imu(SPI_HandleTypeDef &hspi_, uint8_t deviceAddress):
    hspi(&hspi_),
    devAddr(deviceAddress << 1),
    whoAmI(0xFF)
{
    instance = this;
}
Imu::~Imu(){}

bool Imu::init() {
    // who am i 取得 何回か取得
    for(int i=0; i<5; i++){
        readRegister(ICM20648::WHO_AM_I, &whoAmI, 1);
    }

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

    // DMAスタート
    startDMATransfer();
    return true;
}

void Imu::startDMATransfer() {
    txBuffDma[0] = ICM20648::ACCEL_XOUT_H | 0x80;

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive_DMA(hspi, txBuffDma, rxBuffDma, 13);  // DMA転送開始
}

void Imu::handleDMAComplete() {
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    accelRaw.x = (int16_t)((rxBuffDma[1]  << 8) | rxBuffDma[2]);
    accelRaw.y = (int16_t)((rxBuffDma[3]  << 8) | rxBuffDma[4]);
    accelRaw.z = (int16_t)((rxBuffDma[5]  << 8) | rxBuffDma[6]);
    gyroRaw.x  = (int16_t)((rxBuffDma[7]  << 8) | rxBuffDma[8]);
    gyroRaw.y  = (int16_t)((rxBuffDma[9]  << 8) | rxBuffDma[10]);
    gyroRaw.z  = (int16_t)((rxBuffDma[11] << 8) | rxBuffDma[12]);

    HAL_DMA_Abort(hspi->hdmatx);
    HAL_DMA_Abort(hspi->hdmarx);

    startDMATransfer();
}

/*******************************/
/*                             */
/*                             */
/* HAL callback function       */
/*                             */
/*                             */
/*******************************/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI1 && Imu::instance) {
        Imu::instance->handleDMAComplete();
    }
}

bool Imu::writeRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    uint8_t txBuffer[size + 1];
    txBuffer[0] = reg & 0x7F;  // 最上位ビットをクリア (書き込み)
    memcpy(&txBuffer[1], data, size);

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    bool status = (HAL_SPI_Transmit(hspi, txBuffer, size + 1, HAL_MAX_DELAY) == HAL_OK);
    HAL_Delay(1);
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    return status;
}

bool Imu::readRegister(uint8_t reg, uint8_t* data, uint16_t size) {
    uint8_t txBuffer = reg | 0x80;  // 最上位ビットをセット (読み込み)

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    bool status = (HAL_SPI_Transmit(hspi, &txBuffer, 1, HAL_MAX_DELAY) == HAL_OK &&
                   HAL_SPI_Receive(hspi, data, size, HAL_MAX_DELAY) == HAL_OK);
    HAL_Delay(1);
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
