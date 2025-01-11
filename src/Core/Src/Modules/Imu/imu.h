#ifndef IMU_H
#define IMU_H
#include <UsartInterface/usart_interface.h>

class Imu : public UsartInterface{
public:
    Imu();
    ~Imu();
};

#endif
