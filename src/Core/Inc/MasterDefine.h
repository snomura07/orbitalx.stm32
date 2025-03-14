#ifndef INC_MASTERDEFINE_H_
#define INC_MASTERDEFINE_H_
#include <main.h>

#define VERSION "2.0.3"
#define NAME "OrbitalX"

#define LED_ON  0
#define LED_OFF 1
#define PI 3.14f
#define RIGHT_ENC_PPR  18
#define LEFT_ENC_PPR  13
#define WHEEL_DIAMETER 14.3f
#define DELTA_T 0.001
#define DATAFLASH_START_ADDR  0x0800F400
#define RX_BUFFER_SIZE 128
#define TX_BUFFER_SIZE 128

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
