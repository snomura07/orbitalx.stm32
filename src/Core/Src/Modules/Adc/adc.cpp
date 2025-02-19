#include "adc.h"
#include "main.h"

Adc* Adc::instance = nullptr;

Adc::Adc(ADC_HandleTypeDef &hadc_, Iled *iled_ ):
    hadc(&hadc_),
    iled(iled_)
{
    instance = this;
}
Adc::~Adc(){}

void Adc::startDMA() {
      // 二重開始防止
    if (HAL_ADC_GetState(hadc) == HAL_ADC_STATE_BUSY) return;

    HAL_ADC_Start_DMA(hadc, (uint32_t*)adcValues, 7);
}

/*******************************/
/*                             */
/*                             */
/* HAL callback function       */
/*                             */
/*                             */
/*******************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1 && Adc::instance) {
        Adc::instance->handleDMAComplete();
    }
}

void Adc::handleDMAComplete() {
    iled->off();
}
