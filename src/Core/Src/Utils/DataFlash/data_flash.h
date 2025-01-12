#ifndef DATAFLASH_H
#define DATAFLASH_H

#include <cstdint>
#include <cstddef>

class DataFlash {
public:
    static constexpr uint32_t FlashStartAddress = 0x0800F400; // 保存領域の開始アドレス
    static constexpr uint32_t FlashSize = 5 * 1024;           // 保存領域のサイズ (5KB)

    DataFlash();
    ~DataFlash();

    // 2バイト配列をフラッシュに書き込む
    bool writeData(const uint16_t* data, size_t length);

    // フラッシュからデータを読み出して2バイト配列に格納
    bool readData(uint16_t* data, size_t length) const;

private:
    bool unlockFlash() const;
    bool lockFlash() const;
    bool eraseSector(uint32_t address);
    bool writeWord(uint32_t address, uint32_t data) const;
    bool isAddressValid(uint32_t address, size_t size) const;
};

#endif // DATAFLASH_H
