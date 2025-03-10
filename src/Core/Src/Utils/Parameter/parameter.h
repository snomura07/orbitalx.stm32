#ifndef PARAMETER_H
#define PARAMETER_H
#include <DataFlash/data_flash.h>
#include "parameter_address.h"

class Parameter{
public:
    struct PidGain {
        float kP;
        float kI;
        float kD;
    };

public:
    Parameter(DataFlash *dataFlash_);
    ~Parameter();
    void readAll();
    void writePidGainVel(float kp, float ki, float kd);
    void writePidGainAngVel(float kp, float ki, float kd);

private:
    void readIntBlock(uint32_t address, int16_t* outData);
    void readFloatBlock(uint32_t address, float* outData);
    void writeIntBlock(uint32_t address, const int16_t* data);
    void writeFloatBlock(uint32_t address, const float* data);

public:
    PidGain pidGainVel;
    PidGain pidGainAngVel;

private:
    DataFlash *dataFlash;
};

#endif
