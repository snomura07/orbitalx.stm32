#ifndef IMU_H
#define IMU_H

#include "icm_20648.h"
#include <stm32f3xx_hal.h>
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

public:
    Imu(I2C_HandleTypeDef &hi2c_, uint8_t deviceAddress = ICM20648::DEFAULT_ADDRESS);
    ~Imu();
    bool init();
    uint8_t whoAmI();
    void update();
    void dump();

private:
    void readAll();
    bool writeRegister(uint8_t reg, uint8_t* data, uint16_t size);
    bool readRegister (uint8_t reg, uint8_t* data, uint16_t size);

private:
    I2C_HandleTypeDef *hi2c;
    uint8_t devAddr;
};

#endif
