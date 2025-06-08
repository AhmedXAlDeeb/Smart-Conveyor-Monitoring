#ifndef PWM_CONFIG_H
#define PWM_CONFIG_H

#define TIMER_CLOCK_FREQ 8000000UL  // 8 MHz
#define PWM_FREQUENCY    1000U
#define PWM_RESOLUTION   16U
#define PWM_PRESCALER    2
#define PWM_DEFAULT_TIMER TIM1
#define PWM_MODE1        0x6
#define PWM_MODE2        0x7
#define PWM_MODE         PWM_MODE1
#define PWM_DEFAULT_CHANNEL 2 // PA9 = TIM1_CH2

#endif  // PWM_CONFIG_H
