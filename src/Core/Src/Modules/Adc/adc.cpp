#include "adc.h"
#include "main.h"

Adc* Adc::instance = nullptr;

Adc::Adc(ADC_HandleTypeDef &hadc_, Iled *iled_ ):
    hadc(&hadc_),
    iled(iled_),
    rightEncWriteIndex(0),
    rightEncDataCount(0),
    leftEncWriteIndex(0),
    leftEncDataCount(0)
{
    instance = this;
}
Adc::~Adc(){}

void Adc::startDMA() {
      // 二重開始防止
    if (HAL_ADC_GetState(hadc) == HAL_ADC_STATE_BUSY) return;
    HAL_ADC_Start_DMA(hadc, (uint32_t*)adcBuff, 7);
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
    // リングバッファの更新
    rightEncBuff[rightEncWriteIndex] = adcBuff[RIGHT_ENC_CH];
    leftEncBuff[leftEncWriteIndex]   = adcBuff[LEFT_ENC_CH];
    rightEncWriteIndex = (rightEncWriteIndex + 1) % BUFF_SIZE;
    if (rightEncDataCount < BUFF_SIZE) {
        rightEncDataCount++;
    }

    leftEncWriteIndex = (leftEncWriteIndex + 1) % BUFF_SIZE;
    if (leftEncDataCount < BUFF_SIZE) {
        leftEncDataCount++;
    }

    iled->off();
}

void Adc::resetEncDataCount() {
    rightEncDataCount  = 0;
    rightEncWriteIndex = 0;
    leftEncDataCount   = 0;
    leftEncWriteIndex  = 0;
}
