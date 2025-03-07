#ifndef PARAMETER_H
#define PARAMETER_H
#include <UsartInterface/usart_interface.h>
#include <DataFlash/data_flash.h>

class Parameter : public UsartInterface{
public:
    Parameter();
    ~Parameter();
    void init(DataFlash *dataFlash_);

private:
    DataFlash *dataFlash;
};

#endif
