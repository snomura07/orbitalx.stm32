#ifndef IMU_H
#define IMU_H

#include "icm_20648.h"
#include <stm32g4xx_hal.h>
#include <UsartInterface/usart_interface.h>

class Imu : public UsartInterface{
public:
    struct Axis
    {
        int16_t x;
        int16_t y;
        int16_t z;
    };
    Axis accelRaw;
    Axis gyroRaw;
    uint8_t whoAmI;
    static Imu* instance;

public:
    Imu(SPI_HandleTypeDef &hspi_, uint8_t deviceAddress = ICM20648::DEFAULT_ADDRESS);
    ~Imu();
    bool init();
    void update();
    void dump();
    char* getChipName();
    void handleDMAComplete();

private:
    void startDMATransfer();
    void readAll();
    bool writeRegister(uint8_t reg, uint8_t* data, uint16_t size);
    bool readRegister (uint8_t reg, uint8_t* data, uint16_t size);

private:
    SPI_HandleTypeDef *hspi;
    uint8_t devAddr;
    uint8_t txBuffDma[13];  // 最大12バイト + レジスタアドレス
    uint8_t rxBuffDma[13];  // 受信用バッファ
};

#endif
