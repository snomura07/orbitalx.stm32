#ifndef PARAMETER_H
#define PARAMETER_H
#include <DataFlash/data_flash.h>

class Parameter{
public:
    Parameter(DataFlash *dataFlash_);
    ~Parameter();

private:
    DataFlash *dataFlash;
};

#endif
