#include "action_launcher.h"

ActionLauncher::ActionLauncher(Imu *imu_):
    imu(imu_),
    actionIndex(0)
{}
ActionLauncher::~ActionLauncher(){}

void ActionLauncher::select() {
    int16_t gyroY = imu->gyroCorrected.y;
    if(abs(gyroY) > 3500){
        actionIndex++;
        HAL_Delay(100);
    }

    launch();
}

void ActionLauncher::launch() {

}
