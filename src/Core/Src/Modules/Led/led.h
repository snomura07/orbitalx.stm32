#ifndef SRC_MODULES_LED_H_
#define SRC_MODULES_LED_H_

#include <main.h>
#include <UtilInterface/util_interface.h>

class Led : public UtilInterface{
public:
	enum ModeEnum{
		ORANGE,
		GREEN,
		BLUE_FRONT,
		BLUE_BACK,
		RED,
		DARK_GREEN
	};
	ModeEnum mode;

public:
	Led(ModeEnum mode_);
	~Led();
	void on();
	void off();
	void toggle();
};

#endif /* SRC_MODULES_LED_H_ */
