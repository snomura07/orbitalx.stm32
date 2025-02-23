#ifndef SYSTEM_STATE_MACHINE_H_
#define SYSTEM_STATE_MACHINE_H_
#include <main.h>

class StateMachine {
public:
    enum StateEnum {
        BOOT,
        STANDBY,
        SEARCH_RUN,
        FAST_RUN,
        TEST,
    };
    StateEnum currState;

public:
    StateMachine();
    ~StateMachine();
    bool boot2Standby();
    bool standby2Test();
    bool standby2SearchRun();
    bool standby2FastRun();
    char* getStateStr();
};

#endif
