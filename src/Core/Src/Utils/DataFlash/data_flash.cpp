#include "main.h"
#include "data_flash.h"

DataFlash::DataFlash():
    lastErasedPage(0xFFFFFFFF)
{}
DataFlash::~DataFlash() {}

bool DataFlash::writeData(uint32_t address, const uint16_t* data, size_t length) {
    if (!data || length == 0) return false;
    if (!isAddressValid(address, length * 2)) return false;
    if (!unlockFlash()) return false;

    // 同じページのデータを消さないようにする
    uint32_t currentPage = (address - 0x08000000) / FLASH_PAGE_SIZE;
    if (currentPage != lastErasedPage) {
        if (!eraseSector(address)) {
            lockFlash();
            return false;
        }
        lastErasedPage = currentPage;
    }

    uint32_t addr = address;
    for (size_t i = 0; i < length; i += 4) {
        uint64_t doubleWord = 0;
        for (size_t j = 0; j < 4; j++) {
            if (i + j < length) {
                doubleWord |= static_cast<uint64_t>(data[i + j]) << (16 * j);
            }
        }
        if (!writeDoubleWord(addr, doubleWord)) {
            lockFlash();
            return false;
        }
        addr += 8;
    }

    return lockFlash();
}

bool DataFlash::readData(uint32_t address, uint16_t* data, size_t length) const {
    if (!data || length == 0) return false;
    if (!isAddressValid(address, length * 2)) return false;

    uint32_t addr = address;
    for (size_t i = 0; i < length; i += 4) {
        uint64_t doubleWord = *reinterpret_cast<const uint64_t*>(addr);
        for (size_t j = 0; j < 4; j++) {
            if (i + j < length) {
                data[i + j] = static_cast<uint16_t>((doubleWord >> (16 * j)) & 0xFFFF);
            }
        }
        addr += 8;
    }
    return true;
}

bool DataFlash::unlockFlash() const {
    return (HAL_FLASH_Unlock() == HAL_OK);
}

bool DataFlash::lockFlash() const {
    return (HAL_FLASH_Lock() == HAL_OK);
}

bool DataFlash::eraseSector(uint32_t address) {
    uint32_t pageError = 0;
    FLASH_EraseInitTypeDef eraseInitStruct;

    eraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInitStruct.Page = (address - 0x08000000) / FLASH_PAGE_SIZE; // ページ番号を計算
    eraseInitStruct.NbPages = 1;

    return (HAL_FLASHEx_Erase(&eraseInitStruct, &pageError) == HAL_OK);
}

bool DataFlash::writeDoubleWord(uint32_t address, uint64_t data) const {
    return (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data) == HAL_OK);
}

bool DataFlash::isAddressValid(uint32_t address, size_t size) const {
    return (address >= FlashStartAddress &&
            (address + size) <= (FlashStartAddress + FlashSize));
}
