#include "../LIB/Std_Types.h"
#include "../GPIO/GPIO.h"
#include "PWM.h"
#include "PWM_PRIVATE.h"
#include "PWM_Config.h"
#include "../RCC/RCC.h"
#include "../LIB/Utils.h"
#include "../LIB/Bit_Operations.h"

#define PWM_PIN       9
#define PWM_PORT      'A'
#define PWM_AF_NUM    0x1  // AF1 for TIM1_CH2

static uint8 CHANNEL;

void PWM_Init(uint8 channel) {
    CHANNEL = channel;

    Rcc_Enable(RCC_TIM1);
    Rcc_Enable(RCC_GPIOA);

    // Set PA9 as Alternate Function
    GPIO_INIT(PWM_PORT, PWM_PIN, ALT_MODE, PUSH_PULL);

    // Set alternate function AF1 on PA9 (TIM1_CH2)
    uint32 *AFRH = (uint32 *)(GPIOA_BASE_ADDR + 0x24);
    *AFRH &= ~(0xF << ((PWM_PIN - 8) * 4));
    *AFRH |=  (PWM_AF_NUM << ((PWM_PIN - 8) * 4));

    // Timer setup
    uint32 timer_clock = TIMER_CLOCK_FREQ / (PWM_PRESCALER + 1);
    uint32 arr = (timer_clock / PWM_FREQUENCY) - 1;

    TIM1->PSC  = PWM_PRESCALER;
    TIM1->ARR  = arr;
    TIM1->CCR2 = 0;

    if (CHANNEL == 2) {
        TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
        TIM1->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC2M_Pos);
        TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
        TIM1->CCER  |= TIM_CCER_CC2E;
    }

    TIM1->CR1  |= TIM_CR1_ARPE;
    TIM1->EGR  |= TIM_EGR_UG;
    TIM1->BDTR |= (1 << 15);  // Enable Main Output (MOE)
    TIM1->CR1  |= TIM_CR1_CEN;
}

void PWM_SetDutyCycle(uint16 duty_percent) {
    uint32 arr = TIM1->ARR;
    uint32 ccr_value = (duty_percent * (arr + 1)) / 100;

    if (CHANNEL == 2) {
        TIM1->CCR2 = ccr_value;
    }
}

void PWM_Start(void) {
    TIM1->CR1 |= TIM_CR1_CEN;
}

void PWM_Stop(void) {
    TIM1->CR1 &= ~TIM_CR1_CEN;
}
