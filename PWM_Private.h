#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H
#include "../LIB/Std_Types.h"

#define TIM1_BASE   0x40010000UL
#define TIM2_BASE   0x40000000UL
#define TIM3_BASE   0x40000400UL
#define TIM4_BASE   0x40000800UL
#define TIM5_BASE   0x40000C00UL

typedef struct {
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 SMCR;
    volatile uint32 DIER;
    volatile uint32 SR;
    volatile uint32 EGR;
    volatile uint32 CCMR1;
    volatile uint32 CCMR2;
    volatile uint32 CCER;
    volatile uint32 CNT;
    volatile uint32 PSC;
    volatile uint32 ARR;
    volatile uint32 RESERVED1;
    volatile uint32 CCR1;
    volatile uint32 CCR2;
    volatile uint32 CCR3;
    volatile uint32 CCR4;
    volatile uint32 BDTR;     // << Added for TIM1
    volatile uint32 DCR;
    volatile uint32 DMAR;
} TIM_TypeDef;

#define TIM1   ((TIM_TypeDef *)TIM1_BASE)
#define TIM2   ((TIM_TypeDef *)TIM2_BASE)
#define TIM3   ((TIM_TypeDef *)TIM3_BASE)
#define TIM4   ((TIM_TypeDef *)TIM4_BASE)
#define TIM5   ((TIM_TypeDef *)TIM5_BASE)

#endif //PWM_PRIVATE_H
