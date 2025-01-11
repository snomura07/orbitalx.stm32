#ifndef WALL_SENSOR_H
#define WALL_SENSOR_H
#include <UsartInterface/usart_interface.h>

class WallSensor : public UsartInterface{
public:
    WallSensor();
    ~WallSensor();
    void execAdc();

private:
    void turnOnIled();
    void turnOffIled();
};

#endif
