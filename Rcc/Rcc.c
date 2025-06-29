/*
 * RCC.c
 *
 *  Created on: May 1, 2025
 *      Author: Hassnaa Hossam
 */

#include "Rcc.h"

#include "../Lib/Bit_Operations.h"
#include "../Lib/Std_Types.h"
#include "Rcc_Private.h"

void Rcc_Init(void) {
    SET_BIT(RCC_CR, 0);
    //	 RCC_CFGR |= (0x0A << 4); // 8MHz internal
}

void Rcc_Enable(uint8 PeripheralId) {
    uint8 BusId = PeripheralId / 32;
    uint8 PeripheralBitPosition = PeripheralId % 32;

    switch (BusId) {
        case RCC_AHB1:
            SET_BIT(RCC_AHB1ENR, PeripheralBitPosition);
            break;
        case RCC_AHB2:
            SET_BIT(RCC_AHB2ENR, PeripheralBitPosition);
            break;
        case RCC_APB1:
            SET_BIT(RCC_APB1ENR, PeripheralBitPosition);
            break;
        case RCC_APB2:
            SET_BIT(RCC_APB2ENR, PeripheralBitPosition);
            break;
        default:
            break;
    }
}

void Rcc_Disable(uint8 PeripheralId) {
    uint8 BusId = PeripheralId / 32;
    uint8 PeripheralBitPosition = PeripheralId % 32;
    switch (BusId) {
        case RCC_AHB1:
            SET_BIT(RCC_AHB1RSTR, PeripheralBitPosition);
            break;
        case RCC_AHB2:
            SET_BIT(RCC_AHB2RSTR, PeripheralBitPosition);
            break;
        case RCC_APB1:
            SET_BIT(RCC_APB1RSTR, PeripheralBitPosition);
            break;
        case RCC_APB2:
            SET_BIT(RCC_APB2RSTR, PeripheralBitPosition);
            break;
        default:
            break;
    }
}








