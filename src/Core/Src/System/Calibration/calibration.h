#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <WallSensor/wall_sensor.h>
#include <LedController/led_controller.h>

class Calibration : public UtilInterface{
public:
    Calibration();
    ~Calibration();
    void init(WallSensor *wallSensor_, LedController *ledController_);

    void calibrateWallSensorRightSide();
    void calibrateWallSensorLeftSide();


private:
    WallSensor *wallSensor;
    LedController *led;
};

#endif
