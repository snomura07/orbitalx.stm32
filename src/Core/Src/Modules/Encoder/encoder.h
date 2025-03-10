#ifndef ENCODER_H
#define ENCODER_H
#include <UtilInterface/util_interface.h>
#include <Adc/adc.h>

class Encoder : public UtilInterface{
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
    static constexpr uint8_t BUFF_SIZE = 16;
    uint16_t buff[BUFF_SIZE];
    bool upTriggered;
    bool downTriggered;
    int staticCounter;
    uint16_t lastCheckedValue;
    uint16_t staticThreshold;

public:
    uint32_t counter;
    uint16_t currRaw;
    uint16_t preRaw;
};

#endif
