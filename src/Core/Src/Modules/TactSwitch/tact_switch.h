#ifndef TACT_SWITCH_H
#define TACT_SWITCH_H

#include <main.h>
#include <UsartInterface/usart_interface.h>

class TactSwitch : public UsartInterface{
public:
    TactSwitch();
    ~TactSwitch();
    bool isPushed();
};

#endif
