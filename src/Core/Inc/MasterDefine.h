#ifndef INC_MASTERDEFINE_H_
#define INC_MASTERDEFINE_H_
#include <main.h>

#define VERSION "2.0.3"
#define NAME "OrbitalX"

#define LED_ON  0
#define LED_OFF 1
#define DELTA_T 0.001

struct Axis
{
    int16_t x;
    int16_t y;
    int16_t z;
};
struct AxisLong
{
    int32_t x;
    int32_t y;
    int32_t z;
};

struct AxisFloat
{
    float x;
    float y;
    float z;
};

#endif /* INC_MASTERDEFINE_H_ */
