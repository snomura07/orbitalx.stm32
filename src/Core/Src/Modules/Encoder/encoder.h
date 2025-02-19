#ifndef ENCODER_H
#define ENCODER_H
#include <UsartInterface/usart_interface.h>
#include <Adc/adc.h>

class Encoder : public UsartInterface{
public:
	enum ModeEnum{
		RIGHT,
		LEFT,
	};
public:
    Encoder(Adc *adc_, ModeEnum mode_);
    ~Encoder();
    void update();
    void dump();

private:
    void execAdc();
    void countUp();

private:
    Adc *adc;
	ModeEnum mode;
    uint16_t THRE_UP;
    uint16_t THRE_DOWN;
    uint16_t THRE_UP_RIGHT;
    uint16_t THRE_DOWN_RIGHT;
    uint16_t THRE_UP_LEFT;
    uint16_t THRE_DOWN_LEFT;
    static constexpr uint8_t BUFF_SIZE = 16;
    uint16_t buff[BUFF_SIZE];

public:
    uint32_t counter;
    uint16_t currRaw;
    uint16_t preRaw;
};

#endif
