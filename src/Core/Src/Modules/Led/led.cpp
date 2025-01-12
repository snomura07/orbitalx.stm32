#include "led.h"
#include <main.h>
#include <stm32f3xx_hal.h>

Led::Led(ModeEnum mode_){
	this->mode = mode_;
	this->off();
}

Led::~Led(){}

void Led::on(){
	if(this->mode == ModeEnum::BLUE_FRONT){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	}
	else if(this->mode == ModeEnum::BLUE_BACK){
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	}
	else if(this->mode == ModeEnum::ORANGE){
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	}
	else if(this->mode == ModeEnum::GREEN){
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
	}
}

void Led::off(){
	if(this->mode == ModeEnum::BLUE_FRONT){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	}
	else if(this->mode == ModeEnum::BLUE_BACK){
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	}
	else if(this->mode == ModeEnum::ORANGE){
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	}
	else if(this->mode == ModeEnum::GREEN){
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	}
}

void Led::toggle(){
	if(this->mode == ModeEnum::BLUE_FRONT){
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}
	else if(this->mode == ModeEnum::BLUE_BACK){
      HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	}
	else if(this->mode == ModeEnum::ORANGE){
      HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	}
	else if(this->mode == ModeEnum::GREEN){
      HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
	}
}
