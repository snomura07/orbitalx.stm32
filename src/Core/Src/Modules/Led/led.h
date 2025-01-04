#ifndef SRC_MODULES_LED_H_
#define SRC_MODULES_LED_H_

#include <main.h>

class Led {
public:
	enum ModeEnum{
		RED,
		BLUE,
		GREEN1,
		GREEN2,
	};
	ModeEnum mode;

public:
	Led(ModeEnum mode_);
	~Led();
	void on();
	void off();
};

#endif /* SRC_MODULES_LED_H_ */
