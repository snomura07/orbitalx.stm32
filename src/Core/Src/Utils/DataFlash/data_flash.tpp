#ifndef DATAFLASH_TPP
#define DATAFLASH_TPP

#include "data_flash.h"

template <typename T>
bool DataFlash::writeData(uint32_t address, const T& data) {
    return write(address, &data, sizeof(T));
}

template <typename T>
bool DataFlash::readData(uint32_t address, T& data) const {
    return read(address, &data, sizeof(T));
}

#endif // DATAFLASH_TPP
