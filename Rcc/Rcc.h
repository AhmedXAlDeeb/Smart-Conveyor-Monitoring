/**
 * Rcc.h
 *
 *  Created on: Sun Mar 26 2023
 *  Author    : Abdullah Darwish
 */

#ifndef RCC_H
#define RCC_H
#include "Std_Types.h"
#include "Rcc_Private.h"

void Rcc_Init(void);

void Rcc_Enable(uint8 PeripheralId);

void Rcc_Disable(uint8 PeripheralId);

#endif /* RCC_H */
