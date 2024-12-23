Instructions written for Ubuntu (Debian) of simple blink project for STM32G0F6P6 with LED on pin ***PA4***

## How to build and flash

1. Install needed ARM development toolchain and other utilities:
    ```bash
    sudo apt update
    sudo apt install -y cmake git ninja-build gcc-arm-none-eabi stlink-tools
    ```
1. Important: current repository uses submodules so please clone the project ***recursively***:
    ```bash
    git clone --recursive https://github.com/Kotsiubynskyi/stm32_rtos_blink.git blink
    ```
1. Generate build files:
    ```bash
    cd blink
    mkdir build
    cd build
    cmake .. -G Ninja
    ```
1. Build project from ***build*** folder:
    ```bash
    ninja
    ```
1. Insert ST-LINK programmer USB stick and make sure it's visible by OS:
    ```bash
    lsusb|grep ST-LINK
    ```
1. Upload built firmware to MCU:
    ```bash
    st-flash erase && st-flash --reset write blink.bin 0x8000000
    ```
