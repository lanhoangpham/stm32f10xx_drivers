 /*
 * 005SPI_test_sendData.c
 *
 *  Created on: Apr 22, 2023
 *      Author: lanph
 */

#include "stm32f103xx_spi_driver.h"
#include "stm32f103xx_gpio_driver.h"

#include<string.h>

/*
 * PB14 - SPI_MISO
 * PB15 - SPI2_MOSI
 * PB13 - SPI2_SCLK
 * PB12 - SPI2_NSS
 */


void SPI2_GPIOinitS(){
	GPIO_Handle_t SPIpins;

	SPIpins.pGPIOx = GPIOB;
	SPIpins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	SPIpins.GPIO_PinConfig.GPIO_PinOP_AltFunc_PpOp = GPIO_AltPp;
	SPIpins.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_Speed_10MHz;

	GPIO_PeriClockCtr(GPIOB, ENABLE);

	//SCLK
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	GPIO_Init(&SPIpins);

	//MOSI
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
	GPIO_Init(&SPIpins);

	//MISO
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
	GPIO_Init(&SPIpins);

	//NSS
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GPIO_Init(&SPIpins);

}

void SPI2_Init(){
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI2handle.SPI_Config.SPI_DFF = SPI_DFF_16BITS;
	SPI2handle.SPI_Config.SPI_CPOL = SPI_CPHA_LOW;
	SPI2handle.SPI_Config.SPI_CPHA = SPI_CPHA_HIGH;
	SPI2handle.SPI_Config.SPI_SSM = SPI_SSM_EN;

	SPI_PCLK_CTRL(SPI2, ENABLE);

	SPI_Init(&SPI2handle);
}

int main(){

	char use_data[] = "Hello World";

	SPI2_GPIOinitS();

	SPI2_Init();

	//this function make NSS signal high and avoids MODF error
	SPI_SSICtr(SPI2, ENABLE);

	//enable the SPI2 peripheral
	SPI_PeripheralCtrl(SPI2, ENABLE);

	//send data
	SPI_SendData(SPI2, (uint8_t*)use_data, strlen(use_data));

	while(1);

	return 0;
}
