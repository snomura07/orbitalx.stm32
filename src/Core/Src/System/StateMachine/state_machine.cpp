#include "state_machine.h"

StateMachine::StateMachine():
    currState(BOOT)
{}

StateMachine::~StateMachine(){}

char* StateMachine::getStateStr() {
    switch (currState) {
        case BOOT:
            return "BOOT";
        case STANDBY:
            return "STANDBY";
        case SEARCH_RUN:
            return "SEARCH_RUN";
        case FAST_RUN:
            return "FAST_RUN";
        case TEST:
            return "TEST";
    }
}
