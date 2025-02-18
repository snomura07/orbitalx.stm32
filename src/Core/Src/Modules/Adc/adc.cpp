#include "adc.h"

Adc::Adc(ADC_HandleTypeDef &hadc_):
    hadc(&hadc_)
{
}
Adc::~Adc(){}

void Adc::update(){
    execAdc();
}

void Adc::execAdc(){
}

void Adc::dump(){
}
