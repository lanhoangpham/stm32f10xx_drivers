/*
 * 003ButtonInterrupt.c
 *
 *  Created on: Apr 18, 2023
 *      Author: lanph
 */


#include "stm32f103xx_gpio_driver.h"

int main(){

	GPIO_Handle_t GPIOC_Pin1, GPIOC_Pin2, GPIOC_Pin3, GPIOC_Pin4, GPIOC_Pin5, GPIOC_Pin6, GPIOC_Pin7;
	GPIOC_Pin1.pGPIOx = GPIOC;
	GPIOC_Pin2.pGPIOx = GPIOC;
	GPIOC_Pin3.pGPIOx = GPIOC;
	GPIOC_Pin4.pGPIOx = GPIOC;
	GPIOC_Pin5.pGPIOx = GPIOC;
	GPIOC_Pin6.pGPIOx = GPIOC;
	GPIOC_Pin7.pGPIOx = GPIOC;

	GPIOC_Pin1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	GPIOC_Pin2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_2;
	GPIOC_Pin3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
	GPIOC_Pin4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
	GPIOC_Pin5.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	GPIOC_Pin6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
	GPIOC_Pin7.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;

	GPIOC_Pin1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	GPIOC_Pin2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	GPIOC_Pin3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	GPIOC_Pin4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	GPIOC_Pin5.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	GPIOC_Pin6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;
	GPIOC_Pin7.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_ALT;

	GPIOC_Pin1.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;
	GPIOC_Pin2.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;
	GPIOC_Pin3.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;
	GPIOC_Pin4.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;
	GPIOC_Pin5.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;
	GPIOC_Pin6.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;
	GPIOC_Pin7.GPIO_PinConfig.GPIO_PinOutPpOp = GPIO_OutPP;


	GPIOC_Pin1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;
	GPIOC_Pin2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;
	GPIOC_Pin3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;
	GPIOC_Pin4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;
	GPIOC_Pin5.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;
	GPIOC_Pin6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;
	GPIOC_Pin7.GPIO_PinConfig.GPIO_PinSpeed = GPIO_Speed_10MHz;

	GPIO_PeriClockCtr(GPIOC, ENABLE);

	GPIO_Init(&GPIOC_Pin1);
	GPIO_Init(&GPIOC_Pin2);
	GPIO_Init(&GPIOC_Pin3);
	GPIO_Init(&GPIOC_Pin4);
	GPIO_Init(&GPIOC_Pin5);
	GPIO_Init(&GPIOC_Pin6);
	GPIO_Init(&GPIOC_Pin7);

	uint16_t count = 0;

	uint16_t countNumber[9];

	countNumber[0] = 0x3F;
	countNumber[1] = 0x06;
	countNumber[2] = 0x5B;
	countNumber[3] = 0x4f;
	countNumber[4] = 0x66;
	countNumber[5] = 0x6d;
	countNumber[6] = 0x7D;
	countNumber[7] = 0x07;
	countNumber[8] = 0x7F;
	countNumber[9] = 0x67;

	while(1){

		GPIOC->GPIOx_ODR &= ~( 0x7F << 1);

		GPIOC->GPIOx_ODR |= countNumber[count] << 1;

		delay();

		count = (count < 9 ? count + 1 : 0);

	}

	return 0;
}
