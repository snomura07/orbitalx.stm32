#include "imu.h"
#include "icm_20648.h"
Imu* Imu::instance;

Imu::Imu(SPI_HandleTypeDef &hspi_, uint8_t deviceAddress):
    hspi(&hspi_),
    devAddr(deviceAddress << 1),
    whoAmI(0xFF)
{
    instance = this;
    accelOffset = {-100, 0, 2058};
    gyroOffset  = {-6, 0, 9};
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
        HAL_Delay(10);
    }

    // バンク切り替え
    uint8_t bank = 0x20;
    writeRegister(ICM20648::REG_BANK_SEL, &bank, 1);
    HAL_Delay(10);

    // 加速度: ±16g, 11.5Hz-DLPF
    addr = 0x2F;
    writeRegister(ICM20648::ACCEL_CONFIG, &addr, 1);
    HAL_Delay(10);

    // ジャイロ: ±2,000°/s
    addr = 0x06;
    writeRegister(ICM20648::GYRO_CONFIG, &addr, 1);
    HAL_Delay(100);

    // バンク戻す
    bank = 0x00;
    writeRegister(ICM20648::REG_BANK_SEL, &bank, 1);
    HAL_Delay(10);


    // DMAスタート
    startDMATransfer();
    return true;
}

void Imu::update() {
    // 値の数値の取得はDMAで裏で実行
    accelCorrected.x = accelRaw.x - accelOffset.x;
    accelCorrected.y = accelRaw.y - accelOffset.y;
    accelCorrected.z = accelRaw.z - accelOffset.z;
    gyroCorrected.x  = gyroRaw.x  - gyroOffset.x;
    gyroCorrected.y  = gyroRaw.y  - gyroOffset.y;
    gyroCorrected.z  = gyroRaw.z  - gyroOffset.z;
}

void Imu::calcZeroPoint(int32_t samples) {
    AxisLong accelSum = {0, 0, 0};
    AxisLong gyroSum  = {0, 0, 0};

    for (int i = 0; i < samples; i++) {
        HAL_Delay(10);  // 10msごとにサンプリング

        accelSum.x += accelRaw.x;
        accelSum.y += accelRaw.y;
        accelSum.z += accelRaw.z;

        gyroSum.x  += gyroRaw.x;
        gyroSum.y  += gyroRaw.y;
        gyroSum.z  += gyroRaw.z;

        sendInt(i);
        sendMessage(" sum: ");
        sendLong(accelSum.x);
        sendMessage(", ");
        sendLong(accelSum.y);
        sendMessage(", ");
        sendLong(accelSum.z);
        sendMessage(", ");
        sendLong(gyroSum.x);
        sendMessage(", ");
        sendLong(gyroSum.y);
        sendMessage(", ");
        sendLong(gyroSum.z);
        sendMessage("\r\n");
    }

    // 平均値をゼロ点として設定
    accelOffset.x = static_cast<int16_t>(accelSum.x / samples);
    accelOffset.y = static_cast<int16_t>(accelSum.y / samples);
    accelOffset.z = static_cast<int16_t>(accelSum.z / samples);

    gyroOffset.x  = static_cast<int16_t>(gyroSum.x / samples);
    gyroOffset.y  = static_cast<int16_t>(gyroSum.y / samples);
    gyroOffset.z  = static_cast<int16_t>(gyroSum.z / samples);

    sendMessage("accel offset: ");
    sendLong(accelOffset.x);
    sendMessage(", ");
    sendLong(accelOffset.y);
    sendMessage(", ");
    sendLong(accelOffset.z);
    sendMessage("\r\n");
    sendMessage("gyro offset: ");
    sendLong(gyroOffset.x);
    sendMessage(", ");
    sendLong(gyroOffset.y);
    sendMessage(", ");
    sendLong(gyroOffset.z);
    sendMessage("\r\n");
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
    txBuffer[0] = reg;
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
    sendMessage("accel[CORR]: ");
    sendInt(accelCorrected.x);
    sendMessage(", ");
    sendInt(accelCorrected.y);
    sendMessage(", ");
    sendInt(accelCorrected.z);
    sendMessage(", ");

    sendMessage("gyro[CORR] : ");
    sendInt(gyroCorrected.x);
    sendMessage(", ");
    sendInt(gyroCorrected.y);
    sendMessage(", ");
    sendInt(gyroCorrected.z);
    sendMessage(", ");

    sendMessage("accel[RAW]: ");
    sendInt(accelRaw.x);
    sendMessage(", ");
    sendInt(accelRaw.y);
    sendMessage(", ");
    sendInt(accelRaw.z);
    sendMessage(", ");

    sendMessage("gyro[RAW] : ");
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

float Imu::getGyroScale() {
    return ICM20648::GYRO_SCALE;
}

float Imu::getAccelScale() {
    return ICM20648::ACCEL_SCALE;
}
