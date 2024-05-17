/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D28_Pin GPIO_PIN_6
#define D28_GPIO_Port GPIOI
#define FMC_NBL3_Pin GPIO_PIN_5
#define FMC_NBL3_GPIO_Port GPIOI
#define FMC_NBL2_Pin GPIO_PIN_4
#define FMC_NBL2_GPIO_Port GPIOI
#define R_CS_Pin GPIO_PIN_10
#define R_CS_GPIO_Port GPIOG
#define D25_Pin GPIO_PIN_1
#define D25_GPIO_Port GPIOI
#define D24_Pin GPIO_PIN_0
#define D24_GPIO_Port GPIOI
#define D29_Pin GPIO_PIN_7
#define D29_GPIO_Port GPIOI
#define FMC_NBL1_Pin GPIO_PIN_1
#define FMC_NBL1_GPIO_Port GPIOE
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define R_INT_Pin GPIO_PIN_4
#define R_INT_GPIO_Port GPIOB
#define D26_Pin GPIO_PIN_2
#define D26_GPIO_Port GPIOI
#define D23_Pin GPIO_PIN_15
#define D23_GPIO_Port GPIOH
#define D22_Pin GPIO_PIN_14
#define D22_GPIO_Port GPIOH
#define USB1_OVERCURRENT_Pin GPIO_PIN_15
#define USB1_OVERCURRENT_GPIO_Port GPIOC
#define CTP_RST_Pin GPIO_PIN_14
#define CTP_RST_GPIO_Port GPIOC
#define ETH_nINT_Pin GPIO_PIN_2
#define ETH_nINT_GPIO_Port GPIOE
#define FMC_NBL0_Pin GPIO_PIN_0
#define FMC_NBL0_GPIO_Port GPIOE
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
#define D27__IS42S32800G_DQ27_Pin GPIO_PIN_3
#define D27__IS42S32800G_DQ27_GPIO_Port GPIOI
#define SDIO_CD_Pin GPIO_PIN_3
#define SDIO_CD_GPIO_Port GPIOE
#define SDNCAS_Pin GPIO_PIN_15
#define SDNCAS_GPIO_Port GPIOG
#define D2_Pin GPIO_PIN_0
#define D2_GPIO_Port GPIOD
#define D21_Pin GPIO_PIN_13
#define D21_GPIO_Port GPIOH
#define D30_Pin GPIO_PIN_9
#define D30_GPIO_Port GPIOI
#define D3_Pin GPIO_PIN_1
#define D3_GPIO_Port GPIOD
#define MCO1_Pin GPIO_PIN_8
#define MCO1_GPIO_Port GPIOA
#define D31_Pin GPIO_PIN_10
#define D31_GPIO_Port GPIOI
#define USR_BTN_1_Pin GPIO_PIN_6
#define USR_BTN_1_GPIO_Port GPIOC
#define SDCLK_Pin GPIO_PIN_8
#define SDCLK_GPIO_Port GPIOG
#define R_GPIO1_Pin GPIO_PIN_7
#define R_GPIO1_GPIO_Port GPIOG
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOF
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOF
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOF
#define QSPI_BK1_NCS_Pin GPIO_PIN_6
#define QSPI_BK1_NCS_GPIO_Port GPIOG
#define A3_Pin GPIO_PIN_3
#define A3_GPIO_Port GPIOF
#define R_GPIO0_Pin GPIO_PIN_3
#define R_GPIO0_GPIO_Port GPIOG
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOH
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
#define A5_Pin GPIO_PIN_5
#define A5_GPIO_Port GPIOF
#define A4_Pin GPIO_PIN_4
#define A4_GPIO_Port GPIOF
#define QSPI_BK1_IO3_Pin GPIO_PIN_6
#define QSPI_BK1_IO3_GPIO_Port GPIOF
#define QSPI_BK1_IO2_Pin GPIO_PIN_7
#define QSPI_BK1_IO2_GPIO_Port GPIOF
#define QSPI_BK1_IO0_Pin GPIO_PIN_8
#define QSPI_BK1_IO0_GPIO_Port GPIOF
#define USB1_EN_Pin GPIO_PIN_10
#define USB1_EN_GPIO_Port GPIOF
#define QSPI_BK1_IO1_Pin GPIO_PIN_9
#define QSPI_BK1_IO1_GPIO_Port GPIOF
#define USR_LED_1_Pin GPIO_PIN_10
#define USR_LED_1_GPIO_Port GPIOJ
#define R_RST_Pin GPIO_PIN_9
#define R_RST_GPIO_Port GPIOJ
#define D7_Pin GPIO_PIN_10
#define D7_GPIO_Port GPIOE
#define CTP_INT_Pin GPIO_PIN_3
#define CTP_INT_GPIO_Port GPIOH
#define CTP_INT_EXTI_IRQn EXTI3_IRQn
#define SDNWE_Pin GPIO_PIN_5
#define SDNWE_GPIO_Port GPIOH
#define A7_Pin GPIO_PIN_13
#define A7_GPIO_Port GPIOF
#define A8_Pin GPIO_PIN_14
#define A8_GPIO_Port GPIOF
#define D6_Pin GPIO_PIN_9
#define D6_GPIO_Port GPIOE
#define D8_Pin GPIO_PIN_11
#define D8_GPIO_Port GPIOE
#define D18_Pin GPIO_PIN_10
#define D18_GPIO_Port GPIOH
#define D19_Pin GPIO_PIN_11
#define D19_GPIO_Port GPIOH
#define D1_Pin GPIO_PIN_15
#define D1_GPIO_Port GPIOD
#define D0_Pin GPIO_PIN_14
#define D0_GPIO_Port GPIOD
#define LCD_DISP_Pin GPIO_PIN_6
#define LCD_DISP_GPIO_Port GPIOA
#define QSPI_CLK_Pin GPIO_PIN_2
#define QSPI_CLK_GPIO_Port GPIOB
#define A6_Pin GPIO_PIN_12
#define A6_GPIO_Port GPIOF
#define A9_Pin GPIO_PIN_15
#define A9_GPIO_Port GPIOF
#define D9_Pin GPIO_PIN_12
#define D9_GPIO_Port GPIOE
#define D12_Pin GPIO_PIN_15
#define D12_GPIO_Port GPIOE
#define D17_Pin GPIO_PIN_9
#define D17_GPIO_Port GPIOH
#define D20_Pin GPIO_PIN_12
#define D20_GPIO_Port GPIOH
#define SNDRAS_Pin GPIO_PIN_11
#define SNDRAS_GPIO_Port GPIOF
#define A10_Pin GPIO_PIN_0
#define A10_GPIO_Port GPIOG
#define D5_Pin GPIO_PIN_8
#define D5_GPIO_Port GPIOE
#define D10_Pin GPIO_PIN_13
#define D10_GPIO_Port GPIOE
#define SDNE1_Pin GPIO_PIN_6
#define SDNE1_GPIO_Port GPIOH
#define D16_Pin GPIO_PIN_8
#define D16_GPIO_Port GPIOH
#define D15_Pin GPIO_PIN_10
#define D15_GPIO_Port GPIOD
#define D14_Pin GPIO_PIN_9
#define D14_GPIO_Port GPIOD
#define USR_BTN_2_Pin GPIO_PIN_0
#define USR_BTN_2_GPIO_Port GPIOB
#define A11_Pin GPIO_PIN_1
#define A11_GPIO_Port GPIOG
#define D4_Pin GPIO_PIN_7
#define D4_GPIO_Port GPIOE
#define D11_Pin GPIO_PIN_14
#define D11_GPIO_Port GPIOE
#define SDCKE1_Pin GPIO_PIN_7
#define SDCKE1_GPIO_Port GPIOH
#define D13_Pin GPIO_PIN_8
#define D13_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
