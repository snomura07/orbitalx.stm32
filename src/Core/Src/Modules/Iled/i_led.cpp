#include "i_led.h"
#include <main.h>
#include <stm32g4xx_hal.h>

Iled::Iled():
    isOn(false)
{
	this->off();
}
Iled::~Iled(){}

void Iled::on(){
    HAL_GPIO_WritePin(SENS_ON_A_GPIO_Port, SENS_ON_A_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SENS_ON_B_GPIO_Port, SENS_ON_B_Pin, GPIO_PIN_SET);
    isOn = true;
}

void Iled::off(){
    HAL_GPIO_WritePin(SENS_ON_A_GPIO_Port, SENS_ON_A_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SENS_ON_B_GPIO_Port, SENS_ON_B_Pin, GPIO_PIN_RESET);
    isOn = false;
}
