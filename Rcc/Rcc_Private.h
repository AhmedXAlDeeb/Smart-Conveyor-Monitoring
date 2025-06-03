/**
 * Rcc_Private.h
 *
 *  Created on: Sun Mar 26 2023
 *  Author    : Abdullah Darwish
 */

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
#include "Std_Types.h"
#include "Utils.h"

#define RCC_BASE_ADDR       0x40023800
#define RCC_CR              REG32(RCC_BASE_ADDR + 0x00UL)
#define RCC_PLLCFGR         REG32(RCC_BASE_ADDR + 0x04UL)
#define RCC_CFGR            REG32(RCC_BASE_ADDR + 0x08UL)
#define RCC_CIR             REG32(RCC_BASE_ADDR + 0x0CUL)
#define RCC_AHB1RSTR        REG32(RCC_BASE_ADDR + 0x10UL)
#define RCC_AHB2RSTR        REG32(RCC_BASE_ADDR + 0x14UL)
#define RCC_AHB3RSTR        REG32(RCC_BASE_ADDR + 0x18UL)
#define RCC_APB1RSTR        REG32(RCC_BASE_ADDR + 0x20UL)
#define RCC_APB2RSTR        REG32(RCC_BASE_ADDR + 0x24UL)
#define RCC_AHB1ENR         REG32(RCC_BASE_ADDR + 0x30UL)
#define RCC_AHB2ENR         REG32(RCC_BASE_ADDR + 0x34UL)
#define RCC_AHB3ENR         REG32(RCC_BASE_ADDR + 0x38UL)
#define RCC_APB1ENR         REG32(RCC_BASE_ADDR + 0x40UL)
#define RCC_APB2ENR         REG32(RCC_BASE_ADDR + 0x44UL)
#define RCC_AHB1LPENR       REG32(RCC_BASE_ADDR + 0x50UL)
#define RCC_AHB2LPENR       REG32(RCC_BASE_ADDR + 0x54UL)
#define RCC_AHB3LPENR       REG32(RCC_BASE_ADDR + 0x58UL)
#define RCC_APB1LPENR       REG32(RCC_BASE_ADDR + 0x60UL)
#define RCC_APB2LPENR       REG32(RCC_BASE_ADDR + 0x64UL)
#define RCC_BDCR            REG32(RCC_BASE_ADDR + 0x70UL)
#define RCC_CSR             REG32(RCC_BASE_ADDR + 0x74UL)
#define RCC_SSCGR           REG32(RCC_BASE_ADDR + 0x80UL)
#define RCC_PLLI2SCFGR      REG32(RCC_BASE_ADDR + 0x84UL)

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

#endif /* RCC_PRIVATE_H */
