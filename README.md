---
layout: post
title: Riverdi 10.1-inch STM32 Embedded Display - board certification review
author: "kisvegabor"
cover: /assets/cover_cert_standard.webp
---

# LVGL port for the 10.1-inch Riverdi STM32 Embedded Displays (STM32H757XIH6)

This repository contains the __Light and Versatile Graphics Library (LVGL)__ port for the __10.1-inch Riverdi STM32 Embedded Displays__ with *STM32H757XIH6* MCU. It's ready-to-use project template which you can easily import into *STM32CubeIDE* and *STM32CubeMX* (to reconfigure selected peripherals). This project uses the master LVGL release (at the time or writing v9.1.1). It is based on the [LVGL example](https://github.com/riverdi/riverdi-101-stm32h7-lvgl) provided by Riverdi, but this repository is maintained by LVGL.

For more info about LVGL (docs, API, tutorials) please visit [*https://lvgl.io/*](https://lvgl.io/) and [*https://github.com/lvgl/lvgl*](https://github.com/lvgl/lvgl)

![img1](/Docs/img_1.png)

This repository supports all configuration of 10.1-inch *Riverdi STM32 Embedded Displays*:

* [*RVT101HVSNWC00-B*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-optical-bonding-uxtouch-stm32h7-rvt101hvsnwc00-b)
* [*RVT101HVSNWC00*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-air-bonding-uxtouch-stm32h7-rvt101hvsnwc00)
* [*RVT101HVSFWCA0*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-air-bonding-atouch-frame-stm32h7-rvt101hvsfwca0)
* [*RVT101HVSNWCA0*](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-air-bonding-atouch-stm32h7-rvt101hvsnwca0)
* [*RVT101HVSFWN00*](https://riverdi.com/product/10-1-inch-lcd-display-stm32h7-frame-rvt101hvsfwn00)
* [*RVT101HVSNWN00*](https://riverdi.com/product/10-1-inch-lcd-display-stm32h7-rvt101hvsnwn00)

For LVGL project templates for 5-inch and 7-inch *Riverdi STM32 Embedded Displays*, please visit:

* [*riverdi-50-stm32u5-lvgl*](https://github.com/lvgl/lv_port_riverdi_stm32u5)
* [*riverdi-70-stm32h7-lvgl*](https://github.com/lvgl/lv_port_riverdi_70-stm32h7)

## How to import this project to STM32CubeIDE:

[1] Clone this respository (do not forget about *--recursive* flag!):
```
git clone --recursive https://github.com/lvgl/lv_port_riverdi_101-stm32h7
```
[2] Open *STM32CubeIDE* and import project:
```
File => Open Projects from File System... => Directory => Select the "riverdi-101-stm32h7-lvgl/STM32CubeIde" folder => Finish
```
[3] Build the project (for the best performance, please use *Release* configuration with *-Ofast* flag):
```
Project => Build all
```
[4] Upload the firmware to the *Riverdi STM32 Embedded Display*

## What is Riverdi STM32 Embedded Display?

[*Riverdi’s Display STM32 Embedded*](https://riverdi.com/product-category/stm32-embedded-displays/?pr=26938) product series are a comprehensive solution for a variety of applications. With high resolution, high brightness, and a host of features, these displays are designed to meet the most demanding requirements.

Riverdi offers a variety of STM32 touch screen displays, including a brand new 5-inch STM32 display modules in its top-tier embedded screen solutions. With the STM32 7-inch LCD and 10.1-inch STM32 TFT display already on the market, the Riverdi LCD Display STM32 Embedded series is the all-in-one HMI solution well-suited for the most demanding applications.

The STM32 Embedded Displays are not just a product, they are an ecosystem based on the industrial-quality LCD-TFT displays with high-brightness, high-resolution, and industrial touchscreen, the performance and interfaces offered by the STM32 microcontrollers, and the comprehensive technical support with free software and libraries.

## 10.1-inch Riverdi STM32 Embedded Display


Main features of the 10.1-inch __Riverdi STM32 Embedded Display__:

* 10.1-inch TFT display
* 1280x800px resolution
* High brightness 850cd/m2
* Full viewing angles (IPS)
* STM32H757XIH6 (2MB Flash, 1MB RAM) microcontroller
* All STM32H7 interfaces
* Optical bonding
* Industrial projected capacitive touch screen
* Black decorative cover glass
* High quality – zero bad pixels
* 64MB QSPI
* 8MB SDRAM
* TouchGFX and LVGL direct support
* Power Supply: 6V-48V

![img2](/Docs/img_2.png)

* __RS485__
* __RS232__
* __Expansion connector__ - the board offers additional and independent GPIOs over a 40pin, 1.27mm male header. It provides direct access to the GPIOs of MCU STM32, that makes it possible to be easily extended by an addon board for specific application (2x I2C, 1x UART, 1x USART, 1x SPI, 1x USB, 7x PWMs, 2x DACs, 2x ADCs)
* __Fully independent 2x CAN FD__ - applicable in industrial and automotive area
* __Fast-programming SWD port__ - SWD connector allows to program STM32 and QSPI with customer’s applications. Riverdi developed the ST-LINK programming cable that is included in the STM32 Embedded Display sample package (single packing)
* __RiBUS connector__ - in some applications there might be a need to connect a second display in one device. With the STM32 Embedded Display line it is very easy as these displays are equipped with Master RiBUS connector – universal interface to Riverdi’s intelligent displays. In this way, the second display does nots need an external host controller and 2 independent displays can be controlled by one STM32
* __USB__ - can be configured to both Host and Device
* __Haptic feedback driver output__ - a DRV2605L haptic driver on the board (on I2C1) can be used to drive ERM and LRA haptic motors. Enhances feedback and conveys useful information to the users

## Specifications

### CPU and memory

- **MCU** STM32H757XIH6 (Cortex-M7 + M4 core, 480MHz)
- **RAM** 1MB internal, 8MB external (32 bit access)
- **Flash** 2MB internal, 64MB external flash
- **GPU** Chrom-Art (DMA2D)

### Display

- **Resolution** 1280x800
- **Display size** 10.1"
- **Interface** LVDS
- **Color depth** 24bit
- **Technology** IPS
- **DPI** 150 px/inch
- **Touch pad** Industrial Capacitive or no touch

## LVGL Certified Board

<img src="https://lvgl.io/assets/images/cert_standard.png" alt="Standard LVGL certificate for Riverdi STM32 Embedded 10.1 display">

The 10.1-inch Riverdi STM32 Embedded Display board earned Standard LVGL Board Certificate, which means that the device has a decent performance and quality.

<iframe width="560" height="315" src="https://www.youtube.com/embed/NGfRHC7HjAs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## Performance

The drivers are configured for standard double buffering. It means even is a single pixel changes on the screen, the whole screen is updated. 

While the music was played the MCU as running at 100% and reached 20-22 FPS, which is really decent on this high resolution display.

### Frame rate (FPS)

Finally the average frame rate was 25 and it was mostly above 20.

### Memory

The 1280 x 800 display is likely one of the largest I've ever seen driven by a standard MCU. Such a large display necessitates a substantial amount of RAM for frame buffers and general rendering. However, the 10.1-inch Riverdi STM32 Embedded Display board rises to the challenge, offering all the power and memory needed to effectively utilize this exceptional display.

In the video, LVGL was operating in 16-bit mode. This setup required 1280 x 800 x 2 bytes = 2MB for a single frame buffer. Given that the driver configuration used three frame buffers, there was still 2MB available in the 8MB external RAM, and the internal RAM was not utilized by the draw buffers or frame buffers at all.

LVGL itself requires approximately 64kB RAM for the widgets (though the actual size varies depending on the specific user interface). Beyond this, the entire 1MB of internal RAM and the remaining 2MB of external RAM are available for the application. Additionally, images or fonts can be loaded into this space from an SD card or external flash.

The 8MB external RAM is also capable of supporting two 32-bit frame buffers. Therefore, with an adjusted driver configuration, by sacrificing some memory, enhanced color depth can also be achieved.

## Quality

### Display
This board comes with an IPS display so it has amazing viewing angles and brightness too. 

![Viewing angles of the STM32 Embedded 10.1" display](/assets/cert_riverdi_STM32_embedded_10/display.webp)

### Touchpad

Riverdi's 10.1-inch STM32 Embedded Display can be ordered with an industrial grade capacitive touch pad or without touchpad as well.

During our evaluation the touchpad was very accurate and we haven't found any issues with it.

### Robustness

This board is designed for integration into a final product, even in challenging environments. It features a durable build, a smooth front surface, pre-drilled mounting holes, and reliable connectors.

## Conclusion

Riverdi's 10.1-inch STM32 Embedded Display stands out as a high-caliber, professional device, tailored for serious industrial applications. Its exceptional quality is evident, aligning perfectly with the standards of a Professional certificate. The display boasts high brightness, excellent visibility, and vibrant colors, all complemented by an industrial-grade touch panel. These features are integrated into a robust and stable construction. At its core, the device is powered by a powerful and contemporary STM32H7 microcontroller unit (MCU).

On the software front, it utilizes ST's renowned and well-established CubeIDE, ensuring reliability and performance. This display is an ideal choice for those seeking a combination of stability and high performance in industrial applications.

## Buy now

You can purchase the 10.1-inch Riverdi STM32 Embedded Displays from several sources:

- [Riverdi's website](https://riverdi.com/product/10-1-inch-lcd-display-capacitive-touch-panel-optical-bonding-uxtouch-stm32h7-rvt101hvsnwc00-b)
- [Mouser](https://www.mouser.pl/c/?q=RVT101HVSNWC00)
- [TME](https://www.tme.com/us/en-us/katalog/?queryPhrase=RVT101HVSNWC00) 
