#ifndef ICM_20648_H
#define ICM_20648_H

#include <cstdint>

namespace ICM20648 {
    static constexpr uint8_t DEFAULT_ADDRESS = 0x68;

    // USER BANK 0 レジスタ
    static constexpr uint8_t WHO_AM_I       = 0x00;  // デバイスID
    static constexpr uint8_t PWR_MGMT_1     = 0x06;  // 電源管理
    static constexpr uint8_t INT_PIN_CFG    = 0x0F;  // 割り込みピン設定
    static constexpr uint8_t ACCEL_XOUT_H   = 0x2D;  // 加速度X軸 上位バイト
    static constexpr uint8_t ACCEL_XOUT_L   = 0x2E;  // 加速度X軸 下位バイト
    static constexpr uint8_t ACCEL_YOUT_H   = 0x2F;  // 加速度Y軸 上位バイト
    static constexpr uint8_t ACCEL_YOUT_L   = 0x30;  // 加速度Y軸 下位バイト
    static constexpr uint8_t ACCEL_ZOUT_H   = 0x31;  // 加速度Z軸 上位バイト
    static constexpr uint8_t ACCEL_ZOUT_L   = 0x32;  // 加速度Z軸 下位バイト
    static constexpr uint8_t ACCEL_CONFIG   = 0x14;  // 加速度FSR設定
    static constexpr uint8_t ACCEL_CONFIG_2 = 0x15;  // 加速度DLPF設定
    static constexpr uint8_t GYRO_XOUT_H    = 0x33;  // ジャイロX軸 上位バイト
    static constexpr uint8_t GYRO_XOUT_L    = 0x34;  // ジャイロX軸 下位バイト
    static constexpr uint8_t GYRO_YOUT_H    = 0x35;  // ジャイロY軸 上位バイト
    static constexpr uint8_t GYRO_YOUT_L    = 0x36;  // ジャイロY軸 下位バイト
    static constexpr uint8_t GYRO_ZOUT_H    = 0x37;  // ジャイロZ軸 上位バイト
    static constexpr uint8_t GYRO_ZOUT_L    = 0x38;  // ジャイロZ軸 下位バイト
    static constexpr uint8_t GYRO_CONFIG_1  = 0x01;  // ジャイロFSR設定
    static constexpr uint8_t REG_BANK_SEL   = 0x7F;  // レジスタバンク選択
    static constexpr uint8_t SMPLRT_DIV_1   = 0x10;  // サンプルレート分周器（上位）
    static constexpr uint8_t SMPLRT_DIV_2   = 0x11;  // サンプルレート分周器（下位）

    // WHO_AM_Iリセット値
    static constexpr uint8_t WHO_AM_I_DEFAULT = 0xE0;

    // スケール変換用定数
    static constexpr float ACCEL_SCALE = 16.0f / 32768.0f;  // ±16g
    static constexpr float GYRO_SCALE = 2000.0f / 32768.0f; // ±2,000°/s
}

#endif
