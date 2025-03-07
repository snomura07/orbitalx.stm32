#ifndef TACT_SWITCH_H
#define TACT_SWITCH_H

#include <main.h>
#include <UtilInterface/util_interface.h>

class TactSwitch : public UtilInterface{
public:
    TactSwitch();
    ~TactSwitch();
    bool isPushed();
};

#endif
