cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "STM32G0_toolchain.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(blink LANGUAGES C ASM CXX)

add_executable (${PROJECT_NAME}
    src/main.cpp
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal.c
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr.c
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc.c
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr_ex.c
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_gpio.c
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_cortex.c
    STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Source/Templates/system_stm32g0xx.c
    STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Source/Templates/gcc/startup_stm32g030xx.s
    src/freertos/tasks.c
    src/freertos/queue.c
    src/freertos/list.c
    src/freertos/portasm.c
    src/freertos/port.c
    src/freertos/heap_4.c
	)

target_include_directories (${PROJECT_NAME} PRIVATE
    include/
    include/freertos/
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Inc
    STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
    STM32CubeG0/Drivers/CMSIS/Include
    )

target_compile_definitions(${PROJECT_NAME} PRIVATE
    STM32G030xx
    )

set (MCPU                     "-mcpu=cortex-m0plus")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")

set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} -mthumb -Wall -Werror -Os -fno-exceptions")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=memory.map -static -Wl,--start-group -lc -lm -Wl,--end-group")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/${CMAKE_PROJECT_NAME}.bin
)
