#ifndef IMU_H
#define IMU_H

#include "icm_20648.h"
#include <stm32f3xx_hal.h>
#include <UsartInterface/usart_interface.h>

class Imu : public UsartInterface{
public:
    Imu(I2C_HandleTypeDef &hi2c_, uint8_t deviceAddress = ICM20648::DEFAULT_ADDRESS);
    ~Imu();
    bool init();
    uint8_t whoAmI();
    bool readAccel(float& ax, float& ay, float& az);
    bool readGyro(float& gx, float& gy, float& gz);

private:
    bool writeRegister(uint8_t reg, uint8_t data);
    bool readRegister(uint8_t reg, uint8_t* data, uint16_t size);

private:
    I2C_HandleTypeDef *hi2c;
    uint8_t devAddr;
};

#endif
