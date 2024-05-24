# LVGL ported to the 10.1-inch Riverdi STM32 Embedded Displays (STM32H757XIH6)

## Overview

STM32 Embedded 10.1” display is all-in-one complete and open-platform solution being able to independently handle the visual layer of devices with the need for high computing performance. The STM32 Embedded Displays series are industrial-quality LCD-TFT solutions based on the STM32H757XIH6 microcontroller. It has been designed in a way that allows to meet most of the hardware and programming challenges faced by engineers, including access to all interfaces.

## Buy

You can purchase the 10.1-inch Riverdi STM32 Embedded Displays from several sources:

- [Riverdi's website](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-optical-bonding-uxtouch-stm32h7-rvt101hvsnwc00-b)
- [Mouser](https://www.mouser.pl/c/?q=RVT101HVSNWC00)
- [TME](https://www.tme.com/us/en-us/katalog/?queryPhrase=RVT101HVSNWC00) 

## Benchmark

### Buffer configuration
The example is configured for 16-bit RGB565 color format. The project uses LVGL's `LV_DISPLAY_RENDER_MODE_DIRECT` mode with two full screen sized framebuffers in external SDRAM memory. In this mode LVGL renders directly into the framebuffer, and synchronizes the framebuffers (copies the updated areas into the back buffer). Framebuffers are switched in the flush callback. Direct mode is an efficient method if there is enough memory (SRAM or SDRAM) available for two full screen sized buffers.

The buffer configuration can be found in the file [lv_port_riverdi_101-stm32h7/CM7/Core/Src/lvgl_port_display.c](https://github.com/lvgl/lv_port_riverdi_101-stm32h7/CM7/Core/Src/lvgl_port_display.c).

TODO: update benchmark video and certificate links
[![image](https://github.com/lvgl/lv_port_riverdi_101-stm32h7/assets/7599318/88fd9a26-ec84-4f7b-98e8-313cf6a2568f)](![image](https://github.com/lvgl/lv_port_riverdi_101-stm32h7/assets/7599318/cad4801b-928b-4b11-bb2a-8f987625acc9))

## Specification
### CPU and memory

- **MCU** STM32H757XIH6 (Cortex-M7 + M4 core, 480MHz)
- **RAM** 1MB internal, 8MB external (32 bit access)
- **Flash** 2MB internal, 64MB external flash
- **GPU** Chrom-ART (DMA2D)

### Display

- **Resolution** 1280x800
- **Display size** 10.1"
- **Interface** LVDS
- **Color depth** 16bit
- **Technology** IPS
- **DPI** 150 px/inch
- **Touch pad** Industrial Capacitive or no touch

### Others

- RS485, RS232
- Expansion connector (40 GPIOs to access 2x I2C, 1x UART, 1x USART, 1x SPI, 1x USB, 7x PWMs, 2x DACs, 2x ADCs)
- 2x CAN FD
- RiBUS connector
- USB
- Haptic feedback driver output (DRV2605L)

## Getting started
To be able to flash and debug your program you will need to purchase an SWD debug probe which supports the ARM Cortex-M7 core, e.g the STMicro ST-Link V2/V3 or the Segger J-Link.

### Hardware setup
- Connect a 6-48V power supply to the POWER header on the board using the supplied cable. The board draws about 0.96A at 9V (our test board did not start up at 6V).
- Connect a debug probe to the SWD header using the supplied cable.
  
### Software setup
- Install [STM32 CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) with processor support for the STM32H757XIH6.

### Run the project
- Clone the project: `git clone --recursive https://github.com/lvgl/lv_port_riverdi_70-stm32h7`
- Open *STM32CubeIDE* and import project:` File => Open Projects from File System... => Directory => Select the "riverdi-70-stm32h7-lvgl/STM32CubeIde" folder => Finish`
- Build the project (for the best performance, please use *Release* configuration with *-Ofast* flag): `Project => Build all`
- Click the ![image](https://github.com/lvgl/lv_port_riverdi_70-stm32h7/assets/7599318/ad1ba904-f917-4e0c-97b3-1c1ca12cf185) Run button to flash the project
    
### Debugging
- After building the project click the Debug button ![image](https://github.com/lvgl/lv_port_riverdi_70-stm32h7/assets/7599318/369e95fb-dbfb-44d8-9250-0a5f3f8bfc60) to flash the project. You will need to select the correct debug probe for the first run.

## Notes
This repository supports all configuration of 10.1-inch *Riverdi STM32 Embedded Displays*:

* [*RVT101HVSNWC00-B*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-optical-bonding-uxtouch-stm32h7-rvt101hvsnwc00-b)
* [*RVT101HVSNWC00*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-air-bonding-uxtouch-stm32h7-rvt101hvsnwc00)
* [*RVT101HVSFWCA0*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-air-bonding-atouch-frame-stm32h7-rvt101hvsfwca0)
* [*RVT101HVSNWCA0*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-air-bonding-atouch-stm32h7-rvt101hvsnwca0)
* [*RVT101HVSFWN00*](https://riverdi.com/product/10-1-inch-lcd-display-stm32h7-frame-rvt101hvsfwn00)
* [*RVT101HVSNWN00*](https://riverdi.com/product/10-1-inch-lcd-display-stm32h7-rvt101hvsnwn00)

## Contribution and Support

If you find any issues with the development board feel free to open an Issue in this repository. For LVGL related issues (features, bugs, etc) please use the main [lvgl repository](https://github.com/lvgl/lvgl).

If you found a bug and found a solution too please send a Pull request. If you are new to Pull requests refer to [Our Guide](https://docs.lvgl.io/master/CONTRIBUTING.html#pull-request) to learn the basics.
