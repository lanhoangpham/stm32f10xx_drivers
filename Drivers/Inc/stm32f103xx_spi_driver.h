/*
 * stm32f103xx_spi_driver.h
 *
 *  Created on: Apr 21, 2023
 *      Author: lanph
 */

#ifndef INC_STM32F103XX_SPI_DRIVER_H_
#define INC_STM32F103XX_SPI_DRIVER_H_

#include "stm32f103xx.h"

typedef struct{
	uint8_t SPI_DeviceMode;  // master or slave
	uint8_t SPI_BusConfig;	//full duplex - haft duplex - single duplex
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_PinConfig_t;


/**
 * @SPI_device Mode
 */
#define SPI_DEVICE_MODE_MASTER				1
#define SPI_DEVICE_MODE_SLAVE				0

/**
 * @SPI_Bus config
 */
#define SPI_BUS_CONFIG_FD					1
#define SPI_BUS_CONFIG_HD					2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3

/**
 * @SPI_SCLK_SPEED
 */
#define SPI_SCLK_SPEED_DIV2					0
#define SPI_SCLK_SPEED_DIV4					1
#define SPI_SCLK_SPEED_DIV8					2
#define SPI_SCLK_SPEED_DIV16				3
#define SPI_SCLK_SPEED_DIV32				4
#define SPI_SCLK_SPEED_DIV64				5
#define SPI_SCLK_SPEED_DIV128				6
#define SPI_SCLK_SPEED_DIV256				7

/**
 * @SPI_DFF
 */
#define SPI_DFF_8BITS						0
#define SPI_DFF_16BITS						1

/**
 * @SPI_CPHA
 */
#define SPI_CPHA_HIGH						1
#define SPI_CPHA_LOW						0

/**
 * @SPI_CPOL
 */
#define SPI_CPOL_HIGH						1
#define SPI_CPOL_LOW						0

/*
 *@SPI_SSM
 */
#define SPI_SSM_EN							1
#define SPI_SSM_DI							0

/*
 * the bit position of each register of SPI_SR
 */
#define SPI_SR_RXNE 					 	0
#define SPI_SR_TXE 							1
#define SPI_SR_UDR							2
#define SPI_SR_CHSIDE						3
#define SPI_SR_CRCERR 						4
#define SPI_SR_MODF 						5
#define SPI_SR_OVR 							6
#define SPI_SR_BSY		 					7


typedef struct{
	SPI_RegDef_t *pSPIx;
	SPI_PinConfig_t SPI_Config;
}SPI_Handle_t;

void SPI_PCLK_CTRL(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

void SPI_Init(SPI_Handle_t *pSPIx);

void SPI_Deinit(SPI_RegDef_t *pSPIx);

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);

void SPI_PeripheralCtrl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

void SPI_SSICtr(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

















#endif /* INC_STM32F103XX_SPI_DRIVER_H_ */
