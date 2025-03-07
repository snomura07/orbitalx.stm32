#ifndef IMU_H
#define IMU_H

#include <MasterDefine.h>
#include <UtilInterface/util_interface.h>
#include "icm_20648.h"

class Imu : public UtilInterface{
public:
    Axis accelRaw;
    Axis gyroRaw;
    Axis accelOffset;
    Axis gyroOffset;
    Axis accelCorrected;
    Axis gyroCorrected;
    uint8_t whoAmI;
    static Imu* instance;

public:
    Imu(SPI_HandleTypeDef &hspi_, uint8_t deviceAddress = ICM20648::DEFAULT_ADDRESS);
    ~Imu();
    bool init();
    void update();
    void calcZeroPoint(int32_t samples);
    void dump();
    void handleDMAComplete();
    char* getChipName();
    float getGyroScale();
    float getAccelScale();

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
