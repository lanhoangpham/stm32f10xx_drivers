/*
 * stm32f10x.h
 *
 *  Created on: Mar 30, 2023
 *      Author: lanph
 */

/*
 * | : set a bit
 * & : to reset a bit
 * */
#ifndef INC_STM32F10X_H_
#define INC_STM32F10X_H_

#include<stdint.h>

#define __vo 						volatile

/*******************************START: Processor Specific Details*******************************/
/**
 * ARM Cortex M3 Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0					((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1					((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2					((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3					((__vo uint32_t*)0xE000E10C)

/**
 * ARM Cortex M3 Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0					((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1					((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2					((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3					((__vo uint32_t*)0xE000E18C)


/**
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRIORITY0			0
#define NVIC_IRQ_PRIORITY1			1
#define NVIC_IRQ_PRIORITY2			2
#define NVIC_IRQ_PRIORITY3			3
#define NVIC_IRQ_PRIORITY4			4
#define NVIC_IRQ_PRIORITY5			5
#define NVIC_IRQ_PRIORITY6			6
#define NVIC_IRQ_PRIORITY7			7
#define NVIC_IRQ_PRIORITY8			8
#define NVIC_IRQ_PRIORITY9			9
#define NVIC_IRQ_PRIORITY10			10
#define NVIC_IRQ_PRIORITY11			11
#define NVIC_IRQ_PRIORITY12			12
#define NVIC_IRQ_PRIORITY13			13
#define NVIC_IRQ_PRIORITY14			14
#define NVIC_IRQ_PRIORITY15			15


/**
 * ARM Cortex M3 Processor NVIC_IPR register Addresses
 */
#define NVIC_IPR_BASEADDR			0xE000E400U

typedef struct{
	uint32_t NVIC_IPR_ARR[60];
}NVIC_IPR_RefDef_t;

#define NVIC_IPR					((NVIC_IPR_RefDef_t*)NVIC_IPR_BASEADDR)

#define NO_PR_BITS_IMPLEMENTED		4

/*
 * base address of flash and SRAM memories
 * */
#define FLASH_BASEADDR				0x08000000U
#define SRAM_BASEADRR				0x20000000U
#define SRAM						SRAM_BASEADRR
#define ROM_BASEADRR				0x1FFFF000U

/**
 * AHBx and APBx Bus peripheral base address
 */
#define PERIPH_BASEADDR				0x40000000U
#define AHB_PERIPH_BASEADRR			0x40018000U
#define APB1PERIPH_BASEADDR			0x40000000U
#define APB2PERIPH_BASEADDR			0x40010000U

/**
 * Base address of peripheral which hanging on AHB bus
 */
#define RCC_BASEADDR			    (AHB_PERIPH_BASEADRR + 0x9000)

/**
 * Base address of peripheral which hanging on APB1 bus
 */
#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)

/**
 * Base address of peripheral which hanging on APB2 bus
 */
#define AFIO_BaseADDR				(APB2PERIPH_BASEADDR + 0X0000)
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0X0400)
#define GPIOA_BASEADRR				(APB2PERIPH_BASEADDR + 0x0800)
#define GPIOB_BASEADRR				(APB2PERIPH_BASEADDR + 0x0C00)
#define GPIOC_BASEADRR				(APB2PERIPH_BASEADDR + 0x1000)
#define GPIOD_BASEADRR				(APB2PERIPH_BASEADDR + 0x1400)
#define GPIOE_BASEADRR				(APB2PERIPH_BASEADDR + 0x1800)
#define GPIOF_BASEADRR				(APB2PERIPH_BASEADDR + 0x1C00)
#define GPIOG_BASEADRR				(APB2PERIPH_BASEADDR + 0x2000)
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)

/************************************peripheral register definition structures****************/
typedef struct{
	__vo uint32_t GPIOx_CRL;			/*!< Port configuration register low 			Address Offset: 0x00>*/
	__vo uint32_t GPIOx_CRH;			/*!< Port configuration register high 			Address Offset: 0x04>*/
	__vo uint32_t GPIOx_IDR;			/*!< Port input data register		 			Address Offset: 0x08>*/
	__vo uint32_t GPIOx_ODR;			/*!< Port output data register		 			Address Offset: 0x0C>*/
	__vo uint32_t GPIOx_BSRR;			/*!< Port bit set/reset register	 			Address Offset: 0x10>*/
	__vo uint32_t GPIOx_BRR;			/*!< Port bit reset register		 			Address Offset: 0x14>*/
	__vo uint32_t GPIOx_LCKR;			/*!< Port configuration lock register			Address Offset: 0x1C>*/
}GPIO_RegDef_t;

typedef struct {
	__vo uint32_t RCC_CR;
	__vo uint32_t RCC_CFGR;
	__vo uint32_t RCC_CIR;
	__vo uint32_t RCC_APB2RSTR;
	__vo uint32_t RCC_APB1RSTR;
	__vo uint32_t RCC_AHBENR;
	__vo uint32_t RCC_APB2ENR;
	__vo uint32_t RCC_APB1ENR;
	__vo uint32_t RCC_BDCR;
	__vo uint32_t RCC_CSR;
	__vo uint32_t RCC_AHBSTR;
	__vo uint32_t RCC_CFGR2;
}RCC_RegDef_t;


typedef struct {
	__vo uint32_t EXTI_IMR;
	__vo uint32_t EXTI_EMR;
	__vo uint32_t EXTI_RTSR;
	__vo uint32_t EXTI_FTSR;
	__vo uint32_t EXTI_SWIER;
	__vo uint32_t EXTI_PR;
}EXTI_RegDef_t;


typedef struct {
	__vo uint32_t AFIO_EVCR;
	__vo uint32_t AFIO_MAPR1;
	uint32_t AFIO_EXTICR[4];
	__vo uint32_t AFIO_MAPR2;
}AFIO_RegDef_t;


/**
 * Peripheral definitions ( peripheral base address typecasted to AFIO_RegDef_t)
 */
#define AFIO						((AFIO_RegDef_t*)AFIO_BaseADDR)

/**
 * Peripheral definitions ( peripheral base address typecasted to EXTI_RegDef_t)
 */
#define EXTI						((EXTI_RegDef_t*)EXTI_BASEADDR)


/**
 * Peripheral definitions ( peripheral base address typecasted to RCC_RegDef_t)
 */

#define RCC							((RCC_RegDef_t*)RCC_BASEADDR)
/**
 * Peripheral definitions ( peripheral base address typecasted to xxx_RegDef_t)
 */
#define GPIOA						((GPIO_RegDef_t*)GPIOA_BASEADRR)
#define GPIOB						((GPIO_RegDef_t*)GPIOB_BASEADRR)
#define GPIOC						((GPIO_RegDef_t*)GPIOC_BASEADRR)
#define GPIOD						((GPIO_RegDef_t*)GPIOD_BASEADRR)
#define GPIOE						((GPIO_RegDef_t*)GPIOE_BASEADRR)
#define GPIOF						((GPIO_RegDef_t*)GPIOF_BASEADRR)
#define GPIOG						((GPIO_RegDef_t*)GPIOG_BASEADRR)

/**
 * Clock enable MACROS for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()			(RCC->RCC_APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()			(RCC->RCC_APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()			(RCC->RCC_APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()			(RCC->RCC_APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN()			(RCC->RCC_APB2ENR |= (1 << 6))


/**
 * Clock disable MACROS for GPIOx peripherals
 */
#define GPIOA_REG_RESET()			do{ RCC->RCC_APB2RSTR |= (1 << 2);  RCC->RCC_APB2RSTR &= (1 << 2);}while(0)
#define GPIOB_REG_RESET() 			do{ RCC->RCC_APB2RSTR |= (1 << 3);  RCC->RCC_APB2RSTR &= (1 << 3);}while(0)
#define GPIOC_REG_RESET() 			do{ RCC->RCC_APB2RSTR |= (1 << 4);  RCC->RCC_APB2RSTR &= (1 << 4);}while(0)
#define GPIOD_REG_RESET() 			do{ RCC->RCC_APB2RSTR |= (1 << 5);  RCC->RCC_APB2RSTR &= (1 << 5);}while(0)
#define GPIOE_REG_RESET()			do{ RCC->RCC_APB2RSTR |= (1 << 6);  RCC->RCC_APB2RSTR |= (1 << 6);}while(0)

/**
 * Clock enable macros for I2Cx peripherals
 */
#define I2C1_PLCK_EN()			(RCC->RCC_APB1ENR |= (1 << 21))
#define I2C2_PLCK_EN()			(RCC->RCC_APB1ENR |= (1 << 22))

/**
 * Clock enable macros for SPIx peripherals
 */

#define SPI2_PLCK_EN()			(RCC->RCC_APB1ENR |= (1 << 14 ))
#define SPI3_PLCK_EN()			(RCC->RCC_APB1ENR |= (1 << 15 ))
#define SPI1_PLCK_EN()			(RCC->RCC_APB2ENR |= (1 << 12 ))


/**
 * Clock enable macros for USARTx peripherals
 */
#define USART2_PCLK_EN()		(RCC->RCC_APB1ENR |= (1 << 17 ))
#define USART3_PCLK_EN()		(RCC->RCC_APB1ENR |= (1 << 18 ))
#define USART1_PCLK_EN()		(RCC->RCC_APB2ENR |= (1 << 14 ))


/**
 * Clock enable macros for UARTx peripherals
 */
#define UART4_PCLK_EN()			(RCC->RCC_APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()			(RCC->RCC_APB1ENR |= (1 << 20))


/**
 * Clock enable MACROS for AFIO peripherals
 */

#define AFIO_PCLK_EN()			(RCC->RCC_APB2ENR |= ( 1 << 0))

/**
 * Clock enable MACROS for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()			(RCC->RCC_APB2ENR &= ~(1 << 2))
#define GPIOB_PCLK_DI()			(RCC->RCC_APB2ENR &= ~(1 << 3))
#define GPIOC_PCLK_DI()			(RCC->RCC_APB2ENR &= ~(1 << 4))
#define GPIOD_PCLK_DI()			(RCC->RCC_APB2ENR &= ~(1 << 5))
#define GPIOE_PCLK_DI()			(RCC->RCC_APB2ENR &= ~(1 << 6))


/**
 * Clock disable MACROS for AFIO peripherals
 */

#define AFIO_PCLK_DI()			(RCC->RCC_APB2ENR) &= ~( 1 << 0))

/**
 * Clock disable macros for I2Cx peripherals
 */
#define I2C1_PLCK_DI()			(RCC->RCC_APB1ENR &= ~(1 << 21))
#define I2C2_PLCK_DI()			(RCC->RCC_APB1ENR &= ~(1 << 22))

/**
 * Clock disable macros for SPIx peripherals
 */

#define SPI2_PLCK_DI()			(RCC->RCC_APB1ENR &= ~(1 << 14 ))
#define SPI3_PLCK_DI()			(RCC->RCC_APB1ENR &= ~(1 << 15 ))
#define SPI1_PLCK_DI()			(RCC->RCC_APB2ENR &= ~(1 << 12 ))


/**
 * Clock disable macros for USARTx peripherals
 */
#define USART2_PCLK_DI()		(RCC->RCC_APB1ENR &= ~(1 << 17 ))
#define USART3_PCLK_DI()		(RCC->RCC_APB1ENR &= ~(1 << 18 ))
#define USART1_PCLK_DI()		(RCC->RCC_APB2ENR &= ~(1 << 14 ))


/**
 * Clock disable macros for UARTx peripherals
 */
#define UART4_PCLK_DI()			(RCC->RCC_APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()			(RCC->RCC_APB1ENR &= ~(1 << 20))


//some generic macros
#define ENABLE 					1
#define DISNABLE 				0
#define SET						ENABLE
#define RESET					DISNABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET

//GPIO pin number
#define GPIO_PIN_0				0
#define GPIO_PIN_1				1
#define GPIO_PIN_2				2
#define GPIO_PIN_3				3
#define GPIO_PIN_4				4
#define GPIO_PIN_5				5
#define GPIO_PIN_6				6
#define GPIO_PIN_7				7
#define GPIO_PIN_8				8
#define GPIO_PIN_9				9
#define GPIO_PIN_10				10
#define GPIO_PIN_11				11
#define GPIO_PIN_12				12
#define GPIO_PIN_13				13
#define GPIO_PIN_14				14
#define GPIO_PIN_15				15
#define GPIO_PIN_16				16

//Mode
#define HIGH					1
#define LOW						0


// this macros use to get the code for EXTI line from the GPIO Base Address
#define GPIO_BASEADDR_TO_CODE(x)		  ( (x == GPIOA) ? 0 :\
											(x == GPIOB) ? 1 : \
											(x == GPIOC) ? 2 : \
											(x == GPIOD) ? 3 : \
											(x == GPIOE) ? 4 : \
											(x == GPIOF) ? 5 : \
											(x == GPIOG) ? 6 : 0)


/**
 * IRQ (Interrupt Request) Numbers of stm32f10xx MCU
 * TODO: you may complete this list for other peripheral
 */

#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI5_9			23
#define IRQ_NO_EXTI15_10		40





#endif /* INC_STM32F10X_H_ */
