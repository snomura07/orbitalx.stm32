#ifndef MOTOR_H
#define MOTOR_H
#include <UtilInterface/util_interface.h>

class Motor : public UtilInterface{
public:
	enum ModeEnum{
		RIGHT,
		LEFT,
	};

public:
    Motor(TIM_HandleTypeDef &htim_, ModeEnum mode_);
    ~Motor();
    void start();
    void stop();
    void setDuty(uint16_t duty);
private:
    TIM_HandleTypeDef *htim;
	ModeEnum mode;
};

#endif
