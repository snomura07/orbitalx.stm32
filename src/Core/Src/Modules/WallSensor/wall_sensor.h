#ifndef WALL_SENSOR_H
#define WALL_SENSOR_H
#include <UsartInterface/usart_interface.h>

class WallSensor : public UsartInterface{
public:
    WallSensor(ADC_HandleTypeDef &hadc1_, ADC_HandleTypeDef &hadc2_);
    ~WallSensor();
    void update();
    void dump();

private:
    void turnOnIled();
    void turnOffIled();

private:
    ADC_HandleTypeDef *hadc1;
    ADC_HandleTypeDef *hadc2;
    uint16_t sensor1;
    uint16_t sensor2;
};

#endif
