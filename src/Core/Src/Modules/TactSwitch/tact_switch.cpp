#include "tact_switch.h"
#include <main.h>
#include <stm32f3xx_hal.h>
#include <MasterDefine.h>

TactSwitch::TactSwitch(){}
TactSwitch::~TactSwitch() {}

bool TactSwitch::isPushed() {
    return HAL_GPIO_ReadPin(TACT_SW_GPIO_Port, TACT_SW_Pin) == GPIO_PIN_SET;
}
