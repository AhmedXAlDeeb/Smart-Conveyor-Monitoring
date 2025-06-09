#include "Delay.h"
#include "stm32f4xx.h"  // If not available, define SysTick manually

static uint32 ticks_per_ms = 0;

void delay_init(uint32 system_clock_hz) {
    ticks_per_ms = system_clock_hz / 1000;

    SysTick->LOAD  = ticks_per_ms - 1;
    SysTick->VAL   = 0;
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32 ms) {
    for (uint32 i = 0; i < ms; i++) {
        SysTick->VAL = 0;
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    }
}
//
// Created by bassa on 6/7/2025.
//
