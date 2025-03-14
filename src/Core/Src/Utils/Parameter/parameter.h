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
    void writeMachineName(const char* name);
    void writeVersion(const char*  ver);
    void writePidGainVel(float kp, float ki, float kd);
    void writePidGainAngVel(float kp, float ki, float kd);

private:
    void readIntBlock(uint32_t address, int16_t* outData);
    void readFloatBlock(uint32_t address, float* outData);
    void readStringBlock(uint32_t address, char* outData, size_t maxLength);
    void writeIntBlock(uint32_t address, const int16_t* data);
    void writeFloatBlock(uint32_t address, const float* data);
    void writeStringBlock(uint32_t address, const char* str, size_t maxLength);

public:
    PidGain pidGainVel;
    PidGain pidGainAngVel;
    char machineName[16];
    char version[16];

private:
    DataFlash *dataFlash;
};

#endif
