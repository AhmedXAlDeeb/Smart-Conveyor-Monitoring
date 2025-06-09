//
// Created by bassa on 6/7/2025.
//

#ifndef DELAY_H
#define DELAY_H

#include "../Lib/Std_Types.h"

void delay_init(uint32 system_clock_hz); // e.g., 16000000 for 16 MHz
void delay_ms(uint32 ms);

#endif // DELAY_H
