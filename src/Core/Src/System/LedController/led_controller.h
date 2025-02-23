#ifndef SYSTEM_LED_CONTROLLER_H_
#define SYSTEM_LED_CONTROLLER_H_
#include <main.h>
#include <Led/led.h>

class LedController {
public:
    LedController();
    ~LedController();
    void init(Led *led0_, Led *led1_, Led *led2_, Led *led3_, Led *led4_, Led *led5_);
    void on(int8_t num); //in:1 ~ 6
    void allOff();
    void allOn();

private:
    static constexpr uint8_t LED_SIZE = 6;
    Led *ledArr[6];
};

#endif
