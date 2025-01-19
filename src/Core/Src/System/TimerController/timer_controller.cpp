#include "timer_controller.h"

TimerController::TimerController(TIM_HandleTypeDef &htim_):
    htim(&htim_),
    status(false)
{}
TimerController::~TimerController(){}

void TimerController::start(){
    HAL_TIM_Base_Start_IT(htim);
    status = true;
}

void TimerController::stop(){
    HAL_TIM_Base_Stop_IT(htim);
    status = false;
}

bool TimerController::isStarted(){
    return status;
}
