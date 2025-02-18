#include "main.h"
#include "data_flash.h"
#include "stm32g4xx_hal.h" // HALライブラリ

DataFlash::DataFlash() {}
DataFlash::~DataFlash() {}

bool DataFlash::writeData(const uint16_t* data, size_t length) {
    if (!data || length == 0) return false;

    // フラッシュメモリのロック解除
    if (!unlockFlash()) return false;

    // 消去
    if (!eraseSector(FlashStartAddress)) {
        lockFlash();
        return false;
    }

    // 書き込み
    uint32_t address = FlashStartAddress;
    for (size_t i = 0; i < length; i += 2) {
        uint32_t word = 0xFFFFFFFF;

        // 下位16ビット
        word = static_cast<uint32_t>(data[i]) & 0xFFFF;

        // 上位16ビット
        if (i + 1 < length) {
            word |= (static_cast<uint32_t>(data[i + 1]) & 0xFFFF) << 16;
        }

        // 書き込み
        if (!writeWord(address, word)) {
            lockFlash();
            return false;
        }

        address += 4; // 次の4バイトアドレス
    }

    // フラッシュメモリを再ロック
    return lockFlash();
}

bool DataFlash::readData(uint16_t* data, size_t length) const {
    if (!data || length == 0) return false;

    uint32_t address = FlashStartAddress;

    for (size_t i = 0; i < length; i += 2) {
        uint32_t word = *reinterpret_cast<const uint32_t*>(address);

        // 下位16ビット
        data[i] = static_cast<uint16_t>(word & 0xFFFF);

        // 上位16ビット
        if (i + 1 < length) {
            data[i + 1] = static_cast<uint16_t>((word >> 16) & 0xFFFF);
        }

        address += 4; // 次の4バイトアドレス
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
    eraseInitStruct.PageAddress = address;
    eraseInitStruct.NbPages = 1;

    return (HAL_FLASHEx_Erase(&eraseInitStruct, &pageError) == HAL_OK);
}

bool DataFlash::writeWord(uint32_t address, uint32_t data) const {
    return (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) == HAL_OK);
}

bool DataFlash::isAddressValid(uint32_t address, size_t size) const {
    return (address >= FlashStartAddress &&
            (address + size) <= (FlashStartAddress + FlashSize));
}
