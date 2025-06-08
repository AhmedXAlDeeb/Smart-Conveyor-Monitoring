#include "../RCC/Rcc.h"
#include "../GPIO/GPIO.h"
#include "../LCD/LCD.h"
#include "../ADC/ADC_interface.h"
#include "../ADC/ADC_private.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../PWM/PWM.h"
#include "../Delay/Delay.h"



int main(void) {




    // 1. Enable the GPIOA clock (assuming LCD is connected to GPIOA)
    RCC_AHB1ENR |= (1 << 0);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 1);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 2);  // Enable clock for GPIOA
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_ADC1);

    // initialize ADC channel 1
    ADC_Init(GPIOA, 1);

    uint16 motor_speed = 75;       // Example value
    uint16 conveyor_speed = 120;   // Example value
    uint32 object_count = 5;       // Example value
    uint8 emergency_flag = 0;      // 0: normal, 1: emergency
    // 2. Initialize the LCD
    LCD_Init();

    // 3. Send a message to the LCD

    // // 4. Optionally move to second line and print more
    // LCD_SendCommand(0xC0);  // Move to line 2 (0x80 + 0x40)
    // LCD_SendString("LCD Driver!");

    char line1[17] = {0};
    char line2[17] = {0};

    char motor_str[8];
    char conv_str[8];
    char obj_str[6];

    itoa(motor_speed, motor_str, 10);
    itoa(conveyor_speed, conv_str, 10);
    itoa(object_count, obj_str, 10);

    // line1 = "M:<motor>% C:<conveyor>"
    strcpy(line1, "M:");
    strcat(line1, motor_str);
    strcat(line1, "% C:");
    strcat(line1, conv_str);

    // line2 = "Obj:<object_count>"
    strcpy(line2, "Obj:");
    strcat(line2, obj_str);

    LCD_SendCommand(0x01);       // Clear display
    LCD_SendString(line1);       // First line
    LCD_SendCommand(0xC0);       // Move to second line
    LCD_SendString(line2);



    PWM_Init(2);   // PA9 = TIM1_CH2
    PWM_Start();
    // Set PB0 and PB1 as output push-pull
    GPIO_INIT('B', 2, OUTPUT_MODE, PUSH_PULL);  // PB0
    GPIO_INIT('B', 3, OUTPUT_MODE, PUSH_PULL);  // PB1

    // Optional: Set initial value
    GPIO_WritePin('B', 2, 1);  // Set PB0 HIGH
    GPIO_WritePin('B', 3, 0);  // Set PB1 LOW




    while (1) {
        uint16 pot_value = ADC_Conversion();  // Read 0–4095

        // Correct duty calculation
        uint32 duty_percent = ((uint32)pot_value * 100U) / 4095U;

        // Set PWM
        PWM_SetDutyCycle((uint8)duty_percent);  // cast to 8-bit if needed

        // Show on LCD
        char lcd_buf[17];
        itoa(duty_percent, motor_str, 10);
        strcpy(lcd_buf, "PWM: ");
        strcat(lcd_buf, motor_str);
        strcat(lcd_buf, "%     ");  // clear trailing chars

        LCD_SendCommand(0x80);  // First line
        LCD_SendString(lcd_buf);

        // Show ADC raw value
        itoa(pot_value, motor_str, 10);
        LCD_SendCommand(0xC0);  // Second line
        LCD_SendString("ADC:");
        LCD_SendString(motor_str);


        // delay_ms(200);  // Small delay
    }

    return 0;
}


//
// #include "../PWM/PWM.h"
// #include "../Delay/Delay.h"
//
// int main(void)
// {
//     delay_init(8000000); // 8 MHz
//     PWM_Init(2);         // CH2 = PA9 = TIM1_CH2
//     PWM_Start();
//
//     while (1) {
//         PWM_SetDutyCycle(10);  // dim
//         delay_ms(1000);
//
//         PWM_SetDutyCycle(50);  // medium
//         delay_ms(1000);
//
//         PWM_SetDutyCycle(90);  // bright
//         delay_ms(1000);
//     }
// }
