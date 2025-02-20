#ifndef I_LED_H
#define I_LED_H

class Iled{
public:
    Iled();
    ~Iled();
    void on();
	void off();
public:
    bool isOn;
};

#endif
