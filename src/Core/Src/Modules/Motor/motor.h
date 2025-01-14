#ifndef MOTOR_H
#define MOTOR_H
#include <UsartInterface/usart_interface.h>

class Motor : public UsartInterface{
public:
    Motor(TIM_HandleTypeDef &htim2_);
    ~Motor();
    void start();
    void stop();
    void setDuty(uint16_t duty);
private:
    TIM_HandleTypeDef *htim2;
};

#endif
