/*
 * stm32f103xx_gpio_driver.h
 *
 *  Created on: Apr 13, 2023
 *      Author: lanph
 */

#ifndef INC_STM32F103XX_GPIO_DRIVER_H_
#define INC_STM32F103XX_GPIO_DRIVER_H_


#include "stm32f103xx.h"

typedef struct {
	uint8_t GPIO_PinNumber;
	uint8_t	GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinInType;
	uint8_t GPIO_PinOutPpOp;
	uint8_t GPIO_PinAltFunc;
	uint8_t GPIO_PinInterrupt;
}GPIO_PinConfig_t;

/**
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT_ALT		1
#define GPIO_MODE_IT_FT			2
#define GPIO_MODE_IT_RT			3
#define GPIO_MODE_IT_RFT		4

#define GPIO_NO_IT				0

#define GPIO_InFloat			1
#define GPIO_InPuPd				2
#define GPIO_InAnalog			0

#define GPIO_Speed_10MHz 		1
#define GPIO_Speed_2MHz 		2
#define GPIO_Speed_50MHz 		3

#define GPIO_OutPP				0
#define GPIO_OutOD				1

#define GPIO_AltPp				2
#define GPIO_AltOp				3


/**
 * This i s handle structure for a GPIO pin
 */
typedef struct{
	GPIO_RegDef_t *pGPIOx; 				 /*!< This hold the base address of the GPIO port to which the pin belongs>*/
	GPIO_PinConfig_t GPIO_PinConfig;     /*!< This hold the GPIO pin Configuration setting>*/
}GPIO_Handle_t;

void delay(void);


/***********************************************************************************************
 * 							APIs supported to this driver
 * For more information about the APIs check the function definitions
 ***********************************************************************************************/
/*
 * peripheral clock setup
 * */
void GPIO_PeriClockCtr(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
/**
 * init and di-int
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/**
 * read and write data
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNunber);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNunber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNunber);

/**
 * IRQ configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNunber);



















































#endif /* INC_STM32F103XX_GPIO_DRIVER_H_ */




























