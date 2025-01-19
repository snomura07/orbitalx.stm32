cmake_minimum_required(VERSION 3.16)

project(STM32F303K8_Project C CXX ASM)

# クロスコンパイル環境の設定
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# コンパイラの設定
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# コンパイルフラグ
set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Os -ffunction-sections -fdata-sections -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

# リンクフラグ
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_C_FLAGS} -T${CMAKE_SOURCE_DIR}/STM32F303K8TX_FLASH.ld  --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections -static")


# 実行可能ファイルの生成対象ファイル
add_executable(
    ${PROJECT_NAME}.elf
    Core/Src/main.cpp
    Core/Src/stm32f3xx_hal_msp.c
    Core/Src/stm32f3xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/system_stm32f3xx.c
    Core/Startup/startup_stm32f303k8tx.s
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_adc.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_adc_ex.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
    Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c

    Core/Src/Modules/Led/led.cpp
    Core/Src/Modules/Map/map.cpp
    Core/Src/Modules/TactSwitch/tact_switch.cpp
    Core/Src/Modules/WallSensor/wall_sensor.cpp
    Core/Src/Modules/Imu/imu.cpp
    Core/Src/Modules/Motor/motor.cpp
    Core/Src/Modules/Battery/battery.cpp
    Core/Src/Modules/ObjectHub/object_hub.cpp
    Core/Src/Modules/Encoder/encoder.cpp
    Core/Src/System/Debug/Menu/menu.cpp
    Core/Src/System/Startup/startup.cpp
    Core/Src/System/TimerController/timer_controller.cpp
    Core/Src/Utils/Usart/usart.cpp
    Core/Src/Utils/DataFlash/data_flash.cpp
    Core/Src/Interface/UsartInterface/usart_interface.cpp
)

# インクルードディレクトリ
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    Core/Inc
    Core/Src/Modules
    Core/Src/Utils
    Core/Src/Interface
    Core/Src/System
    Drivers/STM32F3xx_HAL_Driver/Inc
    Drivers/CMSIS/Device/ST/STM32F3xx/Include
    Drivers/CMSIS/Include
)

# 定義の設定
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    STM32F303x8
    USE_HAL_DRIVER
    HAL_ADC_MODULE_ENABLED
    HAL_GPIO_MODULE_ENABLED
    HAL_TIM_MODULE_ENABLED
    HAL_I2C_MODULE_ENABLED
    HAL_DMA_MODULE_ENABLED
    HAL_UART_MODULE_ENABLED
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND arm-none-eabi-size ${PROJECT_NAME}.elf
    COMMENT "Displaying the size of the ELF file"
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
INSTALL(
    TARGETS
    ${PROJECT_NAME}.elf
    RUNTIME DESTINATION bin
)
