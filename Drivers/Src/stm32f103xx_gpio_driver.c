/*
 * stm32f103xx_gpio_driver.c
 *
 *  Created on: Apr 13, 2023
 *      Author: lanph
 */

/**
 * driver API requirement:
 * GPIO INITIALIZATION; ENABLE/DISNABLE GPIO PORT CLOCK; READ FROM A GPIO PIN; WRITE TO GPIO PIN
 * CONFIGURE ALTERNATE FUNCTION; INTERRUPT HANDLING
 */

#include "stm32f103xx_gpio_driver.h"

//delay function
void delay(void){
	for (uint32_t i = 0; i < 500000; i ++);
}

/***********************************************************************************************
 * 							APIs supported to this driver
 * For more information about the APIs check the function definitions
 ***********************************************************************************************/
/*
 * peripheral clock setup
 * */
void GPIO_PeriClockCtr(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi){
	if( EnorDi == ENABLE){
		if (pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
			}
		else if (pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
			}
		else if (pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
			}
		else if (pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
			}
	}
	else{
		if (pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		}
		else if (pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}
		else if (pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		}
		else if (pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		}
		else if (pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		}
	}


}
/**
 * initialize and di-int
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

	//get pin number of this GPIO
	uint8_t pinNumber = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

	uint8_t temp;

	//configure for input mode
	if ((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == 0) || (pGPIOHandle->GPIO_PinConfig.GPIO_PinInterrupt >= 2) ){

		temp = (uint8_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinInType << 2;

	}
	//configure for output mode and alternate function
	else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == 1){

		temp = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinOutPpOp) << 2) + pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed;

	}

	//configure for port register high
	 if ( (pinNumber > 7 ) || (pGPIOHandle->GPIO_PinConfig.GPIO_PinInterrupt >= 2)){

		 //clear the pin number
		 pGPIOHandle->pGPIOx->GPIOx_CRH &= ~(0xF << (4 * (pinNumber % 8)));

		 //set pin mode
		 pGPIOHandle->pGPIOx->GPIOx_CRH |= temp << (4 * (pinNumber % 8));

	 }
	 //configure for port register low
	 else if((pinNumber <= 7 ) && (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode < 2)){

		 //clear the pin number
		 pGPIOHandle->pGPIOx->GPIOx_CRL &= ~(0xF << (4 * (pinNumber)));

		 //set pin mode
		 pGPIOHandle->pGPIOx->GPIOx_CRL |= temp << (4 * pinNumber);

	 }

	 /*this part code for interrupt mode*/
	 	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinInterrupt >= 2){

	 		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinInterrupt == GPIO_MODE_IT_FT ){

	 			//configure the FTSR
	 			EXTI->EXTI_FTSR |= (1 << pinNumber);

	 			//clear the corresponding RTSR bit
	 			EXTI->EXTI_RTSR &= ~(1 << pinNumber);

	 		}

	 		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinInterrupt == GPIO_MODE_IT_RT ){

	 			//configure the RTSR pin
	 			EXTI->EXTI_RTSR |= (1 << pinNumber);

	 			//clear the corresponding FTSR pin
	 			EXTI->EXTI_FTSR &= ~(1 << pinNumber);
	 		}

	 		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinInterrupt == GPIO_MODE_IT_RFT ){

	 			//configure the FTSR
	 			EXTI->EXTI_FTSR |= (1 << pinNumber);

	 			//configure the RTSR pin
	 			EXTI->EXTI_RTSR |= (1 << pinNumber);

	 		}

	 		/*configure the GPIO port selection in AFIO_EXTICR*/

	 		//select the port
	 		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

	 		//enable clock for AFIO periphery6al
	 		AFIO_PCLK_EN();

	 		//set the pin
	 		uint8_t temp1 = pinNumber / 4;
	 		uint8_t temp2 = pinNumber % 4;
	 		AFIO->AFIO_EXTICR[temp1] |= portcode << (4 * (temp2));

	 		/*enable the exti interrupt delivery using IMR*/
	 		EXTI->EXTI_IMR |= ( 1 << pinNumber);
	 	}

}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if (pGPIOx == GPIOA){
		GPIOA_PCLK_EN();
	}
	if (pGPIOx == GPIOB){
		GPIOB_PCLK_EN();
	}
	if (pGPIOx == GPIOC){
		GPIOC_PCLK_EN();
	}
	if (pGPIOx == GPIOD){
		GPIOD_PCLK_EN();
	}
	if (pGPIOx == GPIOE){
		GPIOE_PCLK_EN();
	}

}

/**
 * read and write data
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	return pGPIOx->GPIOx_IDR;
}

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNunber){
	uint8_t value = ((pGPIOx->GPIOx_IDR >> PinNunber) & 0x00000001);
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNunber, uint8_t value){
	pGPIOx->GPIOx_ODR |= value << PinNunber;
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value){
	pGPIOx->GPIOx_ODR = value;
}


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNunber){
	pGPIOx->GPIOx_ODR ^=  (1 << PinNunber);
}

/**
 * IRQ configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if (EnorDi == ENABLE ){
		if (IRQNumber <= 31 ){
			//program ISER0 register
			*NVIC_ISER0 |= (1 << (IRQNumber));
		}
		else if( IRQNumber > 31 && IRQNumber < 64){
			//program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96){
			//program ISER1 register: 64 to 96
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64));
		}
	}
	else{
		if (IRQNumber <= 31 ){
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if( IRQNumber > 31 && IRQNumber < 64){
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if ( IRQNumber >= 64 && IRQNumber < 96){
			*NVIC_ICER2 |= (1 << (IRQNumber % 64) );
		}
	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	//1. find out the IPR register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section ) + ( 8 - NO_PR_BITS_IMPLEMENTED);
	//*(NVIC_IPR +  (4 * iprx)) |= IRQPriority << shift_amount;
	NVIC_IPR->NVIC_IPR_ARR[iprx] |= IRQPriority << shift_amount;
}

void GPIO_IRQHandling(uint8_t PinNunber){
	//clear the exti pr register corresponding to the pin number
	if (EXTI->EXTI_PR & ( 1 << PinNunber)){
		//clear
		EXTI->EXTI_PR |= ( 1 << PinNunber);
	}
}




























