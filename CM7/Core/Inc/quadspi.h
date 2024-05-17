/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */
typedef enum
{
  MT25QL512G_SPI_MODE = 0,                 /*!< 1-1-1 commands, Power on H/W default setting */
  MT25QL512G_SPI_2IO_MODE,                 /*!< 1-1-2, 1-2-2 read commands                   */
  MT25QL512G_SPI_4IO_MODE,                 /*!< 1-1-4, 1-4-4 read commands                   */
  MT25QL512G_QPI_MODE                      /*!< 4-4-4 commands                               */
} MT25QL512G_Interface_t;

typedef enum
{
  MT25QL512G_STR_TRANSFER = 0,             /* Single Transfer Rate */
  MT25QL512G_DTR_TRANSFER                  /* Double Transfer Rate */
} MT25QL512G_Transfer_t;

uint8_t CSP_QUADSPI_Init(void);
uint8_t QSPI_DummyCyclesCfg(void);
uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size);
uint8_t CSP_QSPI_WriteMemory_Quad(uint8_t* buffer, uint32_t address, uint32_t buffer_size);
void MX_QUADSPI_Init(void);
uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress, uint32_t EraseEndAddress);
uint8_t CSP_QSPI_EnableMemoryMappedMode(void);
uint8_t CSP_QSPI_Erase_Chip(void);
uint8_t QSPI_Enter4Bytes(void);

#define MEMORY_FLASH_SIZE               0x4000000 /* 512 MBits*/
#define MEMORY_SECTOR_SIZE              0x10000   /* 64kBytes */
#define MEMORY_PAGE_SIZE                0x100     /* 256 bytes */
/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

