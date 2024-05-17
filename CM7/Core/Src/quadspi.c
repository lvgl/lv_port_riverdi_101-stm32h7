/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */
#define CHIP_ERASE_CMD                    0xC7
#define READ_STATUS_REG_CMD              (0x05UL)
#define WRITE_ENABLE_CMD                  0x06
#define READ_CONFIGURATION_REG_CMD       (0x15UL)
#define WRITE_STATUS_REG_CMD             (0x01UL)
#define SECTOR_ERASE_CMD                  0xDC
#define SECTOR_ERASE_CMD_QUAD             0x21
#define QUAD_IN_FAST_PROG_CMD            (0x32UL)
#define FOUR_BYTE_QUAD_IN_FAST_PROG_CMD  (0x34UL)
#define ENTER_QUAD_MODE                  (0x35UL)
#define ENTER_FOUR_BYTE                  (0xB7UL)
#define EXIT_QUAD_MODE                   (0xF5UL)
#define QUAD_OUT_FAST_READ_CMD           (0x6BUL)
#define FOUR_BYTE_QUAD_OUT_FAST_READ_CMD (0x6CUL)
#define RESET_ENABLE_CMD                  0x66
#define RESET_EXECUTE_CMD                 0x99
#define DUMMY_CLOCK_CYCLES_READ_QUAD     (0x0AUL)
#define READ_VOL_CFG_REG_CMD              0x85
#define WRITE_VOL_CFG_REG_CMD             0x81
#define QUAD_INOUT_FAST_READ_CMD          0xEB

#define MT25QL512G_SR_WIP                ((uint8_t)0x01)    /*!< Write in progress */
#define MT25QL512G_SR_WREN               ((uint8_t)0x02)    /*!< Write enable latch */

/* Dummy cycles for STR read mode */
#define MT25TL01G_DUMMY_CYCLES_READ_QUAD  10U
#define MT25TL01G_DUMMY_CYCLES_READ       10U

/* Dummy cycles for DTR read mode */
#define MT25TL01G_DUMMY_CYCLES_READ_DTR       6U
#define MT25TL01G_DUMMY_CYCLES_READ_QUAD_DTR  8U

#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15
#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31
#define WRITE_STATUS_REG3_CMD                 0x11

static uint8_t
QSPI_EnterQuad(void);

uint8_t
QSPI_WriteEnable(uint32_t Mode);

uint8_t
QSPI_AutoPollingMemReady_Quad(void);
/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 25;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_3_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PB2     ------> QUADSPI_CLK
    */
    GPIO_InitStruct.Pin = QSPI_BK1_NCS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(QSPI_BK1_NCS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO3_Pin|QSPI_BK1_IO2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO0_Pin|QSPI_BK1_IO1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(QSPI_CLK_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PB2     ------> QUADSPI_CLK
    */
    HAL_GPIO_DeInit(QSPI_BK1_NCS_GPIO_Port, QSPI_BK1_NCS_Pin);

    HAL_GPIO_DeInit(GPIOF, QSPI_BK1_IO3_Pin|QSPI_BK1_IO2_Pin|QSPI_BK1_IO0_Pin|QSPI_BK1_IO1_Pin);

    HAL_GPIO_DeInit(QSPI_CLK_GPIO_Port, QSPI_CLK_Pin);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

uint8_t
CSP_QSPI_EraseSector (uint32_t EraseStartAddress, uint32_t EraseEndAddress)
{
  QSPI_CommandTypeDef s_command;

  EraseStartAddress = EraseStartAddress
                      - EraseStartAddress % MEMORY_SECTOR_SIZE;
  s_command.Instruction       = SECTOR_ERASE_CMD;
  s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
  s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  while (EraseEndAddress >= EraseStartAddress)
    {
      s_command.Address = (EraseStartAddress & 0x0FFFFFFF);

      if (HAL_OK != QSPI_WriteEnable(MT25QL512G_QPI_MODE))
        return HAL_ERROR;

      if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
        return HAL_ERROR;

      EraseStartAddress += MEMORY_SECTOR_SIZE;

      if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
        return HAL_ERROR;
    }

  return HAL_OK;
}

uint8_t
QSPI_Enter4Bytes (void)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = ENTER_FOUR_BYTE;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
    return HAL_ERROR;

  if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
    return HAL_ERROR;

  return HAL_OK;
}

static uint8_t
QSPI_EnterQuad (void)
{
  QSPI_CommandTypeDef s_command;

  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = ENTER_QUAD_MODE;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
QSPI_WriteEnable (uint32_t Mode)
{
  QSPI_CommandTypeDef sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  sCommand.InstructionMode   = (Mode == MT25QL512G_QPI_MODE) ? QSPI_INSTRUCTION_4_LINES : QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = WRITE_ENABLE_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_NONE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
    return HAL_ERROR;

  sConfig.Match           = MT25QL512G_SR_WREN | (MT25QL512G_SR_WREN << 8);
  sConfig.Mask            = MT25QL512G_SR_WREN | (MT25QL512G_SR_WREN << 8);

  sConfig.MatchMode = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 2;
  sConfig.Interval = 0xf0;
  sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

  sCommand.Instruction = READ_STATUS_REG_CMD;
  sCommand.DataMode = (Mode == MT25QL512G_QPI_MODE) ? QSPI_DATA_4_LINES : QSPI_DATA_1_LINE;

  if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
QSPI_ResetChip (void)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the reset enable command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction       = RESET_ENABLE_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, 5000))
    {
      //return HAL_ERROR;
    }

  HAL_Delay(1);

  /* Initialize the reset enable command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction       = RESET_EXECUTE_CMD ;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, 5000))
    {
      //return HAL_ERROR;
    }
  HAL_Delay(10);


  if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
    {
      //return HAL_ERROR;
    }

  /* Initialize the reset enable command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = RESET_ENABLE_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, 5000))
    {
      //return HAL_ERROR;
    }

  HAL_Delay(1);

  /* Initialize the reset enable command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = RESET_EXECUTE_CMD ;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command(&hqspi, &s_command, 5000))
    {
      //return HAL_ERROR;
    }
  HAL_Delay(10);


  if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
CSP_QSPI_EnableMemoryMappedMode (void)
{
  QSPI_CommandTypeDef      s_command;
  QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;

  s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction       = FOUR_BYTE_QUAD_OUT_FAST_READ_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.DummyCycles       = DUMMY_CLOCK_CYCLES_READ_QUAD;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the memory mapped mode */
  s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
  s_mem_mapped_cfg.TimeOutPeriod     = 0;

  if (HAL_OK != HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg))
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
CSP_QSPI_WriteMemory (uint8_t* buffer, uint32_t address, uint32_t buffer_size)
{
  QSPI_CommandTypeDef s_command;
  uint32_t end_addr, current_size, current_addr;

  current_addr = 0;

  while (current_addr <= address)
    current_addr += MEMORY_PAGE_SIZE;

  current_size = current_addr - address;

  /* Check if the size of the data is less than the remaining place in the page */
  if (current_size > buffer_size)
    current_size = buffer_size;

  /* Initialize the adress variables */
  current_addr = address;
  end_addr = address + buffer_size;

  s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction     = FOUR_BYTE_QUAD_IN_FAST_PROG_CMD;
  s_command.AddressMode     = QSPI_ADDRESS_4_LINES;
  s_command.DataMode        = QSPI_DATA_4_LINES;

  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  do
    {
      s_command.Address = current_addr;
      s_command.NbData = current_size;

      if (current_size == 0)
        return HAL_OK;

      if (HAL_OK != QSPI_WriteEnable( MT25QL512G_QPI_MODE))
        return HAL_ERROR;

      if (HAL_OK != HAL_QSPI_Command( &hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
        return HAL_ERROR;   //  PP failed

      if (HAL_OK != HAL_QSPI_Transmit(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
        return HAL_ERROR;   //  Data failed

      if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
        return HAL_ERROR;   //  Status failed

      current_addr += current_size;
      buffer += current_size;
      current_size = ((current_addr + MEMORY_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : MEMORY_PAGE_SIZE;

    } while (current_addr <= end_addr);

  return HAL_OK;
}

uint8_t
QSPI_AutoPollingMemReady_Quad (void)
{
  QSPI_CommandTypeDef sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  sCommand.InstructionMode = QSPI_INSTRUCTION_4_LINES;
  sCommand.Instruction = READ_STATUS_REG_CMD;
  sCommand.AddressMode = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode = QSPI_DATA_4_LINES;
  sCommand.DummyCycles = 2UL;
  sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.NbData = 1;

  sConfig.Match = 0x00;
  sConfig.Mask = MT25QL512G_SR_WIP | (MT25QL512G_SR_WIP <<8);
  sConfig.MatchMode = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 2;
  sConfig.Interval = 0x10;
  sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_OK != HAL_QSPI_AutoPolling( &hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
CSP_QSPI_Erase_Chip (void)
{
  QSPI_CommandTypeDef s_command;

  if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
   return HAL_ERROR;


  if (HAL_OK != QSPI_WriteEnable(MT25QL512G_QPI_MODE))
    return HAL_ERROR;

  /* Initialize the erase command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction       = CHIP_ERASE_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_OK != HAL_QSPI_Command (&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE))
    return HAL_ERROR;

  if (HAL_OK != QSPI_AutoPollingMemReady_Quad())
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
CSP_QUADSPI_Init (void)
{
  hqspi.Instance = QUADSPI;

  if (HAL_QSPI_DeInit(&hqspi) != HAL_OK)
    return HAL_ERROR;

  MX_QUADSPI_Init();

  if (QSPI_ResetChip() != HAL_OK)
    return HAL_ERROR;

  if (QSPI_Enter4Bytes() != HAL_OK)
    return HAL_ERROR;

  if (QSPI_DummyCyclesCfg() != HAL_OK)
    return HAL_ERROR;

  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
    return HAL_ERROR;

  if (QSPI_EnterQuad() != HAL_OK)
    return HAL_ERROR;

  return HAL_OK;
}

uint8_t
QSPI_DummyCyclesCfg (void)
{
  QSPI_CommandTypeDef s_command;
  uint16_t reg=0;

  /* Initialize the read volatile configuration register command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
  s_command.Instruction       = READ_VOL_CFG_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.DummyCycles       = 0;
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    return HAL_ERROR;

  /* Reception of the data */
  if (HAL_QSPI_Receive(&hqspi, (uint8_t *)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    return HAL_ERROR;

  /* Enable write operations */
  if (QSPI_WriteEnable( MT25QL512G_SPI_MODE) != HAL_OK)
    return HAL_ERROR;

  /* Update volatile configuration register (with new dummy cycles) */
  s_command.Instruction = WRITE_VOL_CFG_REG_CMD;
  MODIFY_REG(reg, 0xF0F0, ((MT25TL01G_DUMMY_CYCLES_READ_QUAD << 4) | (MT25TL01G_DUMMY_CYCLES_READ_QUAD << 12)));

  /* Configure the write volatile configuration register command */
  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    return HAL_ERROR;

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(&hqspi, (uint8_t *)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    return HAL_ERROR;

  /* Return BSP status */
  return HAL_OK;
}

/* USER CODE END 1 */
