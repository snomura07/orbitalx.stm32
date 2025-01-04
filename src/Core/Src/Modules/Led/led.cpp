#include "led.h"
#include <main.h>
#include <stm32f3xx_hal.h>
#include <MasterDefine.h>

Led::Led(ModeEnum mode_){
	this->mode = mode_;
	this->off();
}

Led::~Led(){}

void Led::on(){
	if(this->mode == ModeEnum::RED){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	}
	else if(this->mode == ModeEnum::BLUE){
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	}
	else if(this->mode == ModeEnum::GREEN1){
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	}
	else if(this->mode == ModeEnum::GREEN2){
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
	}
}

void Led::off(){
	if(this->mode == ModeEnum::RED){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	}
	else if(this->mode == ModeEnum::BLUE){
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	}
	else if(this->mode == ModeEnum::GREEN1){
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	}
	else if(this->mode == ModeEnum::GREEN2){
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	}
}
