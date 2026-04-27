#ifndef ZUPT_H
#define ZUPT_H
#include <UtilInterface/util_interface.h>
#include <EncoderDistance/encoder_distance.h>
#include <Imu/imu.h>
#include <Led/led.h>

class Zupt : public UtilInterface{
public:
    Zupt();
    ~Zupt();
    void init(EncoderDistance *encoderDistance_, Imu *imu_, Led *redLed_);
    bool isStopped();
    void update();
    void dump();

private:
    enum StatusEnum {
        STOPPED,
        MOVED
    };

private:
    EncoderDistance *encoderDistance;
    Imu *imu;
    Led *redLed;
    StatusEnum status;
    uint16_t zuptCnt;
};

#endif
