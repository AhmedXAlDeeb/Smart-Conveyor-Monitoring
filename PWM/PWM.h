//
// Created by dell on 6/6/2025.
//

#ifndef PWM_H
#define PWM_H
#include "../LIB/Std_Types.h"

// For Channel 1
#define TIM_CCMR1_OC1M_Pos 4U
#define TIM_CCMR1_OC1M_Msk (0x7 << TIM_CCMR1_OC1M_Pos)  // mask for bits 6:4
#define TIM_CCMR1_OC1M     TIM_CCMR1_OC1M_Msk
#define TIM_CCMR1_OC1PE    (1 << 3)
#define TIM_CCER_CC1E      (1 << 0)

// For Channel 2
#define TIM_CCMR1_OC2M_Pos 12
#define TIM_CCMR1_OC2M     (0xf << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2PE    (1 << 11)
#define TIM_CCER_CC2E      (1 << 4)

// TIMx_CR1 Register Bit Definitions
#define TIM_CR1_CEN        (1 << 0)   // Counter enable
#define TIM_CR1_ARPE       (1 << 7)   // Auto-reload preload enable

// TIMx_EGR Register Bit Definitions
#define TIM_EGR_UG         (1 << 0)   // Update generation

// Channels – update to reflect your actual pin usage
#define CH1  1   // Example: PA0
#define CH2  2   // You are using PA9 → TIM1_CH2
#define CH3  3   // Example: PB0
#define CH4  4   // Example: PB1

void PWM_Init(uint8 channel);
void PWM_SetDutyCycle(uint16 duty_percent);  // Set duty cycle (0 to 100%)
void PWM_Start(void);                        // Start PWM signal
void PWM_Stop(void);                         // Stop PWM signal

#endif // PWM_H
