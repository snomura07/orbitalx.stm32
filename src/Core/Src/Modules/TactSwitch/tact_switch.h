#ifndef TACT_SWITCH_H
#define TACT_SWITCH_H

#include <main.h>

class TactSwitch {
public:
    TactSwitch();
    ~TactSwitch();

    void update();
    bool isPushed();

private:
    bool currState;
    bool preState;

};

#endif
