#include "parameter.h"

Parameter::Parameter(DataFlash *dataFlash_):
    dataFlash(dataFlash_)
{}
Parameter::~Parameter() {}

void Parameter::readAll() {
    float readData[2];
    readFloatBlock(PID_GAIN_VEL_ADDR_1, readData);
    pidGainVel.kP = readData[0];
    pidGainVel.kI = readData[1];

    readFloatBlock(PID_GAIN_VEL_ADDR_2, readData);
    pidGainVel.kD = readData[0];

}

void Parameter::writePidGainVel(float kp, float ki, float kd) {
    float writeData[2];
    writeData[0] = kp;
    writeData[1] = ki;
    writeFloatBlock(PID_GAIN_VEL_ADDR_1, writeData);

    writeData[0] = kd;
    writeData[1] = 0;
    writeFloatBlock(PID_GAIN_VEL_ADDR_2, writeData);

}

void Parameter::readIntBlock(uint32_t address, int16_t* outData) {
    uint16_t readData[4] = {0};
    dataFlash->readData(address, readData, 4);

    for (size_t i = 0; i < 4; i++) {
        outData[i] = static_cast<int16_t>(readData[i]);
    }
}

void Parameter::readFloatBlock(uint32_t address, float* outData) {
    uint16_t readData[4] = {0};
    dataFlash->readData(address, readData, 4);

    for (int i = 0; i < 2; i++) {
        int32_t intValue = static_cast<int32_t>(readData[i * 2]) | (static_cast<int32_t>(readData[i * 2 + 1]) << 16);

        // 符号拡張 (負の数だった場合、上位ビットを補完)
        if (readData[i * 2 + 1] & 0x8000) intValue |= 0xFFFF0000;

        outData[i] = static_cast<float>(intValue) / 1000.0f;
    }
}

void Parameter::writeIntBlock(uint32_t address, const int16_t* data) {
    uint16_t writeData[4] = {0};

    for (size_t i = 0; i < 4; i++) {
        writeData[i] = static_cast<uint16_t>(data[i]);
    }

    dataFlash->writeData(address, writeData, 4);
}

void Parameter::writeFloatBlock(uint32_t address, const float* data) {
    uint16_t writeData[4] = {0};

    for (int i = 0; i < 2; i++) {
        int32_t intValue     = static_cast<int32_t>(data[i] * 1000.0f);  // **1000倍して整数化**
        writeData[i * 2]     = static_cast<uint16_t>(intValue & 0xFFFF);
        writeData[i * 2 + 1] = static_cast<uint16_t>((intValue >> 16) & 0xFFFF);
    }

    dataFlash->writeData(address, writeData, 4);
}
