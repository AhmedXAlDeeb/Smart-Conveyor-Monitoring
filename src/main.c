//
// Created by Lenovo on 09/06/2025.
//

#include "../RCC/Rcc.h"
#include "../GPIO/GPIO.h"
#include "../LCD/LCD.h"
#include "../ADC/ADC_interface.h"
#include "../ADC/ADC_private.h"
#include "../PWM/PWM.h"
#include "../Delay/Delay.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define pot_pin        1
#define IR_button_pin  1

int main(void) {
    // Enable GPIOA, GPIOB, and ADC1 clocks
    RCC_AHB1ENR |= (1 << 0);  // GPIOA
    RCC_AHB1ENR |= (1 << 1);  // GPIOB
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_ADC1);

    // Initialize peripherals
    ADC_Init(GPIOA, pot_pin);
    LCD_Init();
    delay_init(8000000); // For delay_ms

    GPIO_INIT(GPIOB, IR_button_pin, INPUT_MODE, PULL_UP);     // IR button
    GPIO_INIT(GPIOB, 2, OUTPUT_MODE, PUSH_PULL);              // PB2
    GPIO_INIT(GPIOB, 3, OUTPUT_MODE, PUSH_PULL);              // PB3

    GPIO_WritePin(GPIOB, 2, 1); // Optional initial state
    GPIO_WritePin(GPIOB, 3, 0);

    PWM_Init(2);  // PA9 = TIM1_CH2
    PWM_Start();

    // Variables
    uint32 object_count = 0;
    uint16 previous_ir_state = 1;

    char line1[17] = {0};
    char line2[17] = {0};

    char duty_str[8];
    char adc_str[8];
    char obj_str[6];

    while (1) {
        // 1. Read potentiometer
        uint16 pot_value = ADC_Conversion();
        uint32 duty_percent = ((uint32)pot_value * 100U) / 4095U;
        PWM_SetDutyCycle((uint8)duty_percent);  // Update PWM

        // 2. IR object detection on falling edge
        uint16 curr_ir_state = GPIO_ReadPin(GPIOB, IR_button_pin);
        if (previous_ir_state == 1 && curr_ir_state == 0) {
            object_count++;
        }
        previous_ir_state = curr_ir_state;

        // 3. Build LCD strings
        itoa(duty_percent, duty_str, 10);
        itoa(pot_value, adc_str, 10);
        itoa(object_count, obj_str, 10);

        strcpy(line1, "PWM:");
        strcat(line1, duty_str);
        strcat(line1, "% ADC:");
        strcat(line1, adc_str);

        strcpy(line2, "Obj:");
        strcat(line2, obj_str);

        // 4. Update LCD
        LCD_UpdateLine(0, line1);   // Row 0 (first line)
        LCD_UpdateLine(1, line2);   // Row 1 (second line)
        delay_ms(1);
    }

    return 0;
}
