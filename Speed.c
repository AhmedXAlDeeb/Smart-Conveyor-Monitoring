// //
// // Created by Mohamed Yasser on 6/6/2025.
// //
//
// #include "../GPIO/GPIO.h"
// #include "Speed.h"
// #include "Bit_Operations.h"
// #include "Utils.h"
// #include "Rcc.h"
// #include "GPIO.h"
// #include "Std_Types.h"
// #include "Rcc/Rcc.h"
// // #include "stm32f407xx.h"  // For register definitions
//
// /* State variables */
// static uint32 capture1 = 0;
// static uint32 capture2 = 0;
// static uint8 captureState = 0;
// static uint32 lastMeasuredPeriod = 0;
// /* Using TIM3 */
//
// void SpeedMeasurement_Init(void) {
//
//     // Configure PA6 as AF2 for TIM3_CH1
//     GPIO_INIT(0, 6, ALT_MODE, 2);  // Port A, Pin 6, AF2
//
//     // Set prescaler (optional, use if needed)
//     *tim3.PSC = 15;  // Divides 16 MHz to 1 MHz
//
//     // Set auto-reload register to max (optional)
//     *tim3.ARR = 0xFFFF;
//
//     // Configure input capture mode on CH1 (TI1)
//     *tim3.CCMR1 &= ~(0xFF);        // Clear CC1S and IC1F
//     *tim3.CCMR1 |= 0x01;           // CC1S = 01: IC1 is mapped to TI1
//
//     // Enable capture on rising edge
//     *tim3.CCER &= ~(1 << 1);       // CC1P = 0 (rising edge)
//     *tim3.CCER |= (1 << 0);        // CC1E = 1 (enable)
//
//     // Enable interrupt on capture
//     *tim3.DIER |= (1 << 1);        // CC1IE
//
//     // Enable the counter
//     *tim3.CR1 |= (1 << 0);         // CEN
// }
//
// uint8 SpeedMeasurement_GetPeriod(uint32* period) {
//     if (*tim3.SR & (1 << 9)) {  // Check CC1OF (overcapture)
//         *tim3.SR &= ~(1 << 9);
//         captureState = 0;
//         return 0;  // Overflow: invalid reading
//     }
//
//     if (*tim3.SR & (1 << 1)) {  // Check CC1IF
//         *tim3.SR &= ~(1 << 1);  // Clear interrupt flag
//
//         if (captureState == 0) {
//             capture1 = *tim3.CCR1;
//             captureState = 1;
//             return 0;
//         } else {
//             capture2 = *tim3.CCR1;
//
//             if (capture2 >= capture1) {
//                 lastMeasuredPeriod = capture2 - capture1;
//             } else {
//                 lastMeasuredPeriod = (0xFFFF - capture1) + capture2 + 1;
//             }
//
//             *period = lastMeasuredPeriod;
//             captureState = 0;
//             return 1;
//         }
//     }
//
//     return 0;
// }
//
// float SpeedMeasurement_GetFrequency(uint32 timerClockFreq) {
//     if (lastMeasuredPeriod == 0) {
//         return 0.0f;
//     }
//     return ((float)timerClockFreq / lastMeasuredPeriod);
// }
