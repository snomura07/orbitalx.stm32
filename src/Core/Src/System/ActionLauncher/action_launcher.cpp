#include "action_launcher.h"

ActionLauncher::ActionLauncher():
    actionIndex(0)
{}
ActionLauncher::~ActionLauncher(){}

void ActionLauncher::init(Imu *imu_, LedController *ledController_, WallSensor *wallSensor_, RunCore *runCore_) {
    imu           = imu_;
    ledController = ledController_;
    wallSensor    = wallSensor_;
    runCore       = runCore_;
}

void ActionLauncher::select() {
    bool loopFlag = true;
    actionIndex   = 0;
    ledController->on(actionIndex);

    while(loopFlag){
        int16_t gyroX = imu->gyroCorrected.x;
        int16_t gyroY = imu->gyroCorrected.y;
        if(abs(gyroY) > 5000){
            actionIndex++;
            if(actionIndex >= EnumSize){
                actionIndex = 0;
            }
            ledController->on(actionIndex);
            HAL_Delay(500);
        }

        if(abs(gyroX) > 5000){
            loopFlag = false;
            ledController->allOn();
            HAL_Delay(1000);
        }

        HAL_Delay(10);
    }

    launch();
}

void ActionLauncher::launch() {
    standbyStay();

    switch (actionIndex)
    {
        case SearchRun:
            while(1){ledController->on(0);}
            break;
        case FastRun:
            while(1){ledController->on(1);}
            break;
        case Test1:
            runCore->moveForward(200.0);
            break;
        case Test2:
            while(1){ledController->on(3);}
            break;
        case Test3:
            while(1){ledController->on(4);}
            break;
        case Test4:
            while(1){ledController->on(5);}
            break;
    }
}

void ActionLauncher::standbyStay() {
    bool loopFlag = true;
    while(loopFlag){
        ledController->launchBlink();
        if(wallSensor->rFront > 3500){
            loopFlag = false;
            ledController->allOff();
            ledController->allOn();
            HAL_Delay(1000);
            ledController->allOff();
            HAL_Delay(1000);
        }
        HAL_Delay(10);
    }
}
