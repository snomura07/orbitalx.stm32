cmake_minimum_required(VERSION 3.16)

project(STM32G431CBT6_Project C CXX ASM)

# クロスコンパイル環境の設定
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# コンパイラの設定
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# コンパイルフラグ
set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Os -ffunction-sections -fdata-sections -fno-inline-functions -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

# リンクフラグ
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_C_FLAGS} -T${CMAKE_SOURCE_DIR}/STM32G431CBTX_FLASH.ld  --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections -static")


# 実行可能ファイルの生成対象ファイル
add_executable(
    ${PROJECT_NAME}.elf
    Core/Src/main.cpp
    Core/Src/stm32g4xx_hal_msp.c
    Core/Src/stm32g4xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/system_stm32g4xx.c
    Core/Startup/startup_stm32g431cbtx.s
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc_ex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi_ex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
    Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c

    Core/Src/Modules/Led/led.cpp
    Core/Src/Modules/Map/map.cpp
    # Core/Src/Modules/TactSwitch/tact_switch.cpp
    Core/Src/Modules/WallSensor/wall_sensor.cpp
    Core/Src/Modules/Iled/i_led.cpp
    Core/Src/Modules/Imu/imu.cpp
    Core/Src/Modules/Motor/motor.cpp
    Core/Src/Modules/Battery/battery.cpp
    Core/Src/Modules/ObjectHub/object_hub.cpp
    Core/Src/Modules/Encoder/encoder.cpp
    Core/Src/Modules/TimerCount/timer_count.cpp
    Core/Src/Modules/Log/log.cpp
    Core/Src/Modules/Adc/adc.cpp
    Core/Src/System/Startup/startup.cpp
    Core/Src/System/TimerController/timer_controller.cpp
    Core/Src/System/FailSafe/fail_safe.cpp
    Core/Src/System/Logger/logger.cpp
    Core/Src/System/ActionLauncher/action_launcher.cpp
    Core/Src/System/LedController/led_controller.cpp
    Core/Src/System/MotorController/motor_controller.cpp
    Core/Src/System/RunCore/run_core.cpp
    Core/Src/System/Debug/Menu/menu.cpp
    Core/Src/System/MonitorGateway/monitor_gateway.cpp
    Core/Src/Dynamics/DynamicsHub/dynamics_hub.cpp
    Core/Src/Dynamics/AngularVelocity/angular_velocity.cpp
    Core/Src/Dynamics/Angle/angle.cpp
    Core/Src/Dynamics/Accel/accel.cpp
    Core/Src/Dynamics/Velocity/velocity.cpp
    Core/Src/Dynamics/Distance/distance.cpp
    Core/Src/Dynamics/EncoderDistance/encoder_distance.cpp
    Core/Src/Utils/Usart/usart.cpp
    Core/Src/Utils/DataFlash/data_flash.cpp
    Core/Src/Utils/Parameter/parameter.cpp
    Core/Src/Utils/Custom/custom.cpp
    Core/Src/Interface/UtilInterface/util_interface.cpp
)

# インクルードディレクトリ
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    Core/Inc
    Core/Src/Modules
    Core/Src/Utils
    Core/Src/Interface
    Core/Src/System
    Core/Src/Dynamics
    Drivers/STM32G4xx_HAL_Driver/Inc
    Drivers/CMSIS/Device/ST/STM32G4xx/Include
    Drivers/CMSIS/Include
)

# 定義の設定
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    STM32G431xx
    USE_HAL_DRIVER
    HAL_PWR_MODULE_ENABLED
    HAL_ADC_MODULE_ENABLED
    HAL_GPIO_MODULE_ENABLED
    HAL_TIM_MODULE_ENABLED
    # HAL_I2C_MODULE_ENABLED
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
