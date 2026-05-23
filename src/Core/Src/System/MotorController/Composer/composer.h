#ifndef COMPOSER_H
#define COMPOSER_H

#include <Battery/battery.h>

namespace MotorController
{
class Composer {
public:
    Composer();
    ~Composer();
    void init(Battery *battery_);
    void compose(float fbuv, float fbuw, float ffuv);

public:
    float uRight;
    float uLeft;

private:
    Battery *battery;
};
}

#endif
