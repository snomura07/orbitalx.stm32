#include "motor.h"
#include <main.h>
#include <stm32f3xx_hal.h>

Motor::Motor(TIM_HandleTypeDef &htim2_):
    htim2(&htim2_)
{
}

Motor::~Motor(){}

void Motor::start(){
    HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_1);
}

void Motor::stop(){
    HAL_TIM_PWM_Stop(htim2, TIM_CHANNEL_1);
}

void Motor::setDuty(uint16_t duty){
	  HAL_GPIO_WritePin(MOTB_IN1_GPIO_Port, MOTB_IN1_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(htim2, TIM_CHANNEL_1, duty);
}
