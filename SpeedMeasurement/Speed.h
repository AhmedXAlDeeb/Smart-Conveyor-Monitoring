//
// Created by Mohamed Yasser on 6/6/2025.
//

#ifndef SPEED_H_
#define SPEED_H_

#include "Std_Types.h"

/* Base address for TIM3 */
#define TIM3_BASE_ADDR        0x40000400UL  // TIM3 base address

/* Timer register offsets */
#define TIMER_CR1_OFFSET      0x00
#define TIMER_DIER_OFFSET     0x0C
#define TIMER_SR_OFFSET       0x10
#define TIMER_CCMR1_OFFSET    0x18
#define TIMER_CCER_OFFSET     0x20
#define TIMER_PSC_OFFSET      0x28
#define TIMER_ARR_OFFSET      0x2C
#define TIMER_CCR1_OFFSET     0x34

/* Timer register structure */
typedef struct {
    volatile uint32 *CR1;
    volatile uint32 *PSC;
    volatile uint32 *ARR;
    volatile uint32 *CCMR1;
    volatile uint32 *CCER;
    volatile uint32 *DIER;
    volatile uint32 *SR;
    volatile uint32 *CCR1;
} TIMER_RegDef;

/* Macro to initialize TIMER_RegDef */
#define TIMER_INIT(base_addr) { \
(volatile uint32*)(base_addr + TIMER_CR1_OFFSET), \
(volatile uint32*)(base_addr + TIMER_PSC_OFFSET), \
(volatile uint32*)(base_addr + TIMER_ARR_OFFSET), \
(volatile uint32*)(base_addr + TIMER_CCMR1_OFFSET), \
(volatile uint32*)(base_addr + TIMER_CCER_OFFSET), \
(volatile uint32*)(base_addr + TIMER_DIER_OFFSET), \
(volatile uint32*)(base_addr + TIMER_SR_OFFSET), \
(volatile uint32*)(base_addr + TIMER_CCR1_OFFSET) \
}


/* Function prototypes */
void SpeedMeasurement_Init(void);
uint8 SpeedMeasurement_GetPeriod(uint32* period);
float SpeedMeasurement_GetFrequency(uint32 timerClockFreq);

#endif /* SPEED_H_ */
