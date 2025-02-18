#ifndef ENCODER_H
#define ENCODER_H
#include <UsartInterface/usart_interface.h>

class Encoder : public UsartInterface{
public:
	enum ModeEnum{
		RIGHT,
		LEFT,
	};
public:
    Encoder(ADC_HandleTypeDef &hadc_, ModeEnum mode_);
    ~Encoder();
    void update();
    void dump();

private:
    void execAdc();
    void countUp();

private:
    ADC_HandleTypeDef *hadc;
	ModeEnum mode;
    uint16_t THRE_UP;
    uint16_t THRE_DOWN;

    uint16_t uCnt;
    uint16_t max;
    uint16_t min;
    uint16_t currThreUP;
    uint16_t currThreDown;

public:
    uint32_t counter;
    uint16_t currRaw;
    uint16_t preRaw;
};

#endif
