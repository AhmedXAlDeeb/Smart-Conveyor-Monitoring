/*
 * RCC.h
 *
 *  Created on: May 1, 2025
 *      Author: Hassnaa Hossam
 */

#ifndef RCC_H_
#define RCC_H_



#include "../Lib/Std_Types.h"

#define RCC_AHB1 0UL
#define RCC_AHB2 1UL
#define RCC_APB1 2UL
#define RCC_APB2 3UL

#define RCC_GPIOA           (RCC_AHB1*32 + 0UL)
#define RCC_GPIOB           (RCC_AHB1*32 + 1UL)
#define RCC_GPIOC           (RCC_AHB1*32 + 2UL)
#define RCC_GPIOD           (RCC_AHB1*32 + 3UL)
#define RCC_GPIOE           (RCC_AHB1*32 + 4UL)
#define RCC_GPIOH           (RCC_AHB1*32 + 7UL)
#define RCC_CRC             (RCC_AHB1*32 + 2UL)
#define RCC_DMA1            (RCC_AHB1*32 + 21UL)
#define RCC_DMA2            (RCC_AHB1*32 + 22UL)

#define RCC_OTGFS           (RCC_AHB2*32 + 7UL)

#define RCC_TIM2            (RCC_APB1*32 + 0UL)
#define RCC_TIM3            (RCC_APB1*32 + 1UL)
#define RCC_TIM4            (RCC_APB1*32 + 2UL)
#define RCC_TIM5            (RCC_APB1*32 + 3UL)
#define RCC_WWDG            (RCC_APB1*32 + 11UL)
#define RCC_SPI2            (RCC_APB1*32 + 14UL)
#define RCC_SPI3            (RCC_APB1*32 + 15UL)
#define RCC_USART2          (RCC_APB1*32 + 17UL)
#define RCC_I2C1            (RCC_APB1*32 + 21UL)
#define RCC_I2C2            (RCC_APB1*32 + 22UL)
#define RCC_I2C3            (RCC_APB1*32 + 23UL)
#define RCC_PWR             (RCC_APB1*32 + 28UL)

#define RCC_TIM1            (RCC_APB2*32 + 0UL)
#define RCC_USART1          (RCC_APB2*32 + 4UL)
#define RCC_USART6          (RCC_APB2*32 + 5UL)
#define RCC_ADC1            (RCC_APB2*32 + 8UL)
#define RCC_SDIO            (RCC_APB2*32 + 11UL)
#define RCC_SPI1            (RCC_APB2*32 + 12UL)
#define RCC_SPI4            (RCC_APB2*32 + 13UL)
#define RCC_SYSCFG          (RCC_APB2*32 + 14UL)
#define RCC_TIM9            (RCC_APB2*32 + 16UL)
#define RCC_TIM10           (RCC_APB2*32 + 17UL)
#define RCC_TIM11           (RCC_APB2*32 + 18UL)

void Rcc_Init(void);

void Rcc_Enable(uint8 PeripheralId);

void Rcc_Disable(uint8 PeripheralId);





#endif /* RCC_H_ */
