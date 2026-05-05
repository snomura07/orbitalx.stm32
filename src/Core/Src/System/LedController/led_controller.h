#ifndef SYSTEM_LED_CONTROLLER_H_
#define SYSTEM_LED_CONTROLLER_H_
#include <main.h>
#include <Led/led.h>

class LedController {
public:
    using LedEnum = Led::ModeEnum;

public:
    LedController();
    ~LedController();
    void init(Led *blueFront_, Led *blueBack_, Led *orange_, Led *green_, Led *red_, Led *darkGreen_);
    void turnOn(LedEnum no);
    void turnOff(LedEnum no);
    void turnOnLevel(int8_t num);
    void allOff();
    void allOn();
    void launchBlink();

private:
    Led *ledArr[6];
    bool blinkToggle;
};

#endif
