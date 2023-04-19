/*
 * 004.c
 *
 *  Created on: Apr 19, 2023
 *      Author: lanph
 */



#include <string.h>
#include "stm32f103xx_gpio_driver.h"


int main(void)
{
   GPIO_Handle_t GPIOxLed, GPIO_Btn;

   memset(&GPIOxLed, 0, sizeof(GPIOxLed));
   memset(&GPIO_Btn, 0, sizeof(GPIO_Btn));

   GPIOxLed.pGPIOx = GPIOA;
   GPIOxLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
   GPIOxLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
   GPIOxLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_2MHz;
   GPIOxLed.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;

   GPIO_PeriClockCtr(GPIOA, ENABLE );
   //GPIOC_PCLK_EN();

   GPIO_Init(&GPIOxLed);

   GPIO_PeriClockCtr(GPIOC, ENABLE );

   GPIO_Btn.pGPIOx = GPIOC;
   GPIO_Btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
   GPIO_Btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
   GPIO_Btn.GPIO_PinConfig.GPIO_PinInterrupt = GPIO_MODE_IT_RT;
   GPIO_Btn.GPIO_PinConfig.GPIO_PinInType = GPIO_InPuPd;

   GPIO_Init(&GPIO_Btn);

   //set thanh bit 10 cua thanh ghi ODR--> pull up
   GPIO_Btn.pGPIOx->GPIOx_ODR |= (1 <<  GPIO_Btn.GPIO_PinConfig.GPIO_PinNumber);

   //IRQ configuration
   GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
   GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIORITY1);
   while(1){
	   GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_1, ENABLE);
   }

   return 0;




}


void EXTI15_10_IRQHandler(void){
	GPIO_IRQHandling(10);//clear the pending event from the exti line
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_1);
}
