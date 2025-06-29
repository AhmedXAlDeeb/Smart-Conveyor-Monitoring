/*
 * RCC_Private.h
 *
 *  Created on: May 1, 2025
 *      Author: Hassnaa Hossam
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_


#include "../Lib/Std_Types.h"
#include "../Lib/Utils.h"

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





#endif /* RCC_PRIVATE_H_ */
