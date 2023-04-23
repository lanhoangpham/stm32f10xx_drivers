/*
 * stm32f103xx_spi_driver.c
 *
 *  Created on: Apr 21, 2023
 *      Author: lanph
 */
#include "stm32f103xx_spi_driver.h"

void SPI_PCLK_CTRL(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if ( EnorDi == ENABLE){
		if (pSPIx == SPI1 ){
			SPI1_PLCK_EN();
		}
		else if(pSPIx == SPI2){
			SPI2_PLCK_EN();
		}
		else if(pSPIx == SPI3){
			SPI2_PLCK_EN();
		}
	}
	else{
		if (pSPIx == SPI1 ){
				SPI1_PLCK_DI();
			}
			else if(pSPIx == SPI2){
				SPI2_PLCK_DI();
			}
			else if(pSPIx == SPI3){
				SPI2_PLCK_DI();
			}
	}
}

void SPI_Init(SPI_Handle_t *pSPIx){

	uint16_t temp = 0;

	//configure the device mode ( master or slave)
	temp = (pSPIx->SPI_Config.SPI_DeviceMode << 2);

	if( pSPIx->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		//configure for full duplex mode
		temp &= ~( 1 << 15);
	}else if (pSPIx->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		//configure for half duplex mode
		temp |= ( 1 << 15);
	}else if(pSPIx->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//clear BIDI mode
		temp &= ~( 1 << 10);
		//configure for single duplex mode
		temp |= ( 1 << 10);
	}

	//configure for DFF mode
	if ( pSPIx->SPI_Config.SPI_DFF == SPI_DFF_16BITS){
		temp |= (pSPIx->SPI_Config.SPI_DFF << 11);
	}else{
		temp &= ~(pSPIx->SPI_Config.SPI_DFF << 11);
	}

	//configure for speed
	temp |= (pSPIx->SPI_Config.SPI_SclkSpeed << 5);

	//configure for cpol
	temp |= (pSPIx->SPI_Config.SPI_CPOL << 1);

	//configure for cpha
	temp |= (pSPIx->SPI_Config.SPI_CPHA << 0);

	//configure for ssm
	temp |= ( pSPIx->SPI_Config.SPI_SSM << 9);

	pSPIx->pSPIx->SPI_CR1 = temp;

}

void SPI_Deinit(SPI_RegDef_t *pSPIx);

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t bitAddr){
	uint8_t temp = ((pSPIx->SPI_SR >> bitAddr) & 1) ? 1 : 0;
	return temp;
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len){
	while(len > 0){
		//wait until the TXE is empty
		while(!(SPI_GetFlagStatus(pSPIx, 1) == 1)){}

		//check the DFF bit in CR1
		if((pSPIx->SPI_CR1 & ( 1 << 11))){
			//16 bits DFF

			//1. load the data in to the DR
			pSPIx->SPI_DR = (*(uint16_t*)pTxBuffer);
			(len--);
			len--;
			(uint16_t*)pTxBuffer++;
		}
		else{
			//8 bits DFF

			//1 load data into the DR
			pSPIx->SPI_DR = *pTxBuffer;
			len--;
			pTxBuffer++;
		}


	}
}


void SPI_PeripheralCtrl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if ( EnorDi == ENABLE){
		pSPIx->SPI_CR1 |= ( 1 << 6);
	}else{
		pSPIx->SPI_CR1 &= ~( 1 << 6);
	}
}

void SPI_SSICtr(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if ( EnorDi == ENABLE){
			pSPIx->SPI_CR1 |= ( 1 << 8);
		}else{
			pSPIx->SPI_CR1 &= ~( 1 << 8);
		}
}


