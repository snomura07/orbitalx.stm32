#include "main.h"
#include "data_flash.h"

DataFlash::DataFlash() {}
DataFlash::~DataFlash() {}

bool DataFlash::writeData(uint32_t address, const uint16_t* data, size_t length) {
    if (!data || length == 0) return false;
    if (!isAddressValid(address, length * 2)) return false;

    const uint32_t pageStart = FlashBaseAddress + ((address - FlashBaseAddress) / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
    const uint32_t pageEnd   = pageStart + FLASH_PAGE_SIZE;
    const uint32_t writeEnd  = address + static_cast<uint32_t>(length * 2);

    // This implementation updates one flash page at a time.
    if (writeEnd > pageEnd) return false;

    const size_t pageWordLength = FLASH_PAGE_SIZE / sizeof(uint16_t);
    uint16_t pageBuffer[FLASH_PAGE_SIZE / sizeof(uint16_t)] = {0};

    // Backup full page.
    for (size_t i = 0; i < pageWordLength; ++i) {
        pageBuffer[i] = *reinterpret_cast<const uint16_t*>(pageStart + static_cast<uint32_t>(i * sizeof(uint16_t)));
    }

    // Patch only target region in RAM buffer.
    const size_t offsetWords = (address - pageStart) / sizeof(uint16_t);
    for (size_t i = 0; i < length; ++i) {
        pageBuffer[offsetWords + i] = data[i];
    }

    if (!unlockFlash()) return false;

    if (!eraseSector(pageStart)) {
        lockFlash();
        return false;
    }

    uint32_t writeAddr = pageStart;
    for (size_t i = 0; i < pageWordLength; i += 4) {
        uint64_t doubleWord = 0;
        for (size_t j = 0; j < 4; ++j) {
            doubleWord |= static_cast<uint64_t>(pageBuffer[i + j]) << (16 * j);
        }

        if (!writeDoubleWord(writeAddr, doubleWord)) {
            lockFlash();
            return false;
        }
        writeAddr += 8;
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
    eraseInitStruct.Page = (address - FlashBaseAddress) / FLASH_PAGE_SIZE;
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
