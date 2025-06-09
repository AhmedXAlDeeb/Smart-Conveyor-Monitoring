//
// Created by EMAN on 6/6/2025.
//
//
#include "EXIT_private.h"
#include "../LIB/Std_Types.h"
#ifndef EXTI_H
#define EXTI_H

#define interrupt_portA_code  0x0
#define interrupt_portB_code  0x1
#define interrupt_portC_code  0x2
#define interrupt_portD_code  0x3
#define interrupt_portE_code  0x4

#define non_maskable 1
#define  RISING_TRIGGER   				0
#define  FALLING_TRIGGER  				1
#define  RISING_AND_FALLING_TRIGGER  	2

typedef struct {
    volatile uint32 IMR;
    volatile uint32 EMR;
    volatile uint32 RTSR;
    volatile uint32 FTSR;
    volatile uint32 SWIER;
    volatile uint32 PR;
} ExtiType;

typedef struct {
    uint32 NVIC_ISER[8];
    uint32  NVIC_ICER[8];
}NVICType;

void EXTI_Init(uint8 pin , uint8 Port , uint8 trigger);
void EXTI_Enable(uint8 pin);
void EXTI_Disable(uint8 pin);
uint8 EXTI_GetIRQn(uint8 pin);

#endif
