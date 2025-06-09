// //
// // Created by Lenovo on 09/06/2025.
// //
//
// #include "../RCC/Rcc.h"
// #include "../GPIO/GPIO.h"
// #include "../LCD/LCD.h"
// #include "../ADC/ADC_interface.h"
// #include "../ADC/ADC_private.h"
// #include "../SpeedMeasurement/Speed.h"
//
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
//
// int main(void) {
//     // 1. Enable the GPIOA clock (assuming LCD is connected to GPIOA)
//     RCC_AHB1ENR |= (1 << 0);  // Enable clock for GPIOA
//     RCC_AHB1ENR |= (1 << 1);  // Enable clock for GPIOA
//     RCC_AHB1ENR |= (1 << 2);  // Enable clock for GPIOA
//     Rcc_Enable(RCC_GPIOA);
//     Rcc_Enable(RCC_GPIOB);
//     Rcc_Enable(RCC_ADC1);
//     Rcc_Enable(RCC_TIM2);     // For timer capture
//
//     // initialize ADC channel 1
//     ADC_Init(GPIOA, 1);
//
//     uint32 object_count = 5;       // Example value
//     uint8 emergency_flag = 0;      // 0: normal, 1: emergency
//     // 2. Initialize the LCD
//     LCD_Init();
//
//     // Initialize Speed Measurement (TIM2_CH1 - PA0)
//     SpeedMeasurement_Init();
//
//     // 3. Send a message to the LCD
//
//     // // 4. Optionally move to second line and print more
//     // LCD_SendCommand(0xC0);  // Move to line 2 (0x80 + 0x40)
//     // LCD_SendString("LCD Driver!");
//
//     char line1[17] = {0};
//     char line2[17] = {0};
//
//     char motor_str[8];
//     char conv_str[8];
//     char obj_str[6];
// /*
//     //itoa(motor_speed, motor_str, 10);
//     //itoa(conveyor_speed, conv_str, 10);
//     itoa(object_count, obj_str, 10);
//
//     // line1 = "M:<motor>% C:<conveyor>"
//     strcpy(line1, "M:");
//     strcat(line1, motor_str);
//     strcat(line1, "% C:");
//     strcat(line1, conv_str);
//
//     // line2 = "Obj:<object_count>"
//     strcpy(line2, "Obj:");
//     strcat(line2, obj_str);
//
//     LCD_SendCommand(0x01);       // Clear display
//     LCD_SendString(line1);       // First line
//     LCD_SendCommand(0xC0);       // Move to second line
//     LCD_SendString(line2);
// */
//     //LCD_SendString("Hello, LCD!");
//     while (1) {
//     	uint16 pot_value = ADC_Conversion();
//         uint16 motor_speed = (pot_value * 100) / 4095;
//
//         // 4. Read conveyor speed from input capture
//         float frequency = Get_SignalFrequency();
//         uint16 conveyor_speed = (uint16)frequency; // Hz
//
//         // 5. Convert to strings
//         itoa(motor_speed, motor_str, 10);
//         itoa(conveyor_speed, conv_str, 10);
//         itoa(object_count, obj_str, 10);
//
//         // 6. Format LCD lines
//         strcpy(line1, "M:");
//         strcat(line1, motor_str);
//         strcat(line1, "% C:");
//         strcat(line1, conv_str);
//
//         strcpy(line2, "Obj:");
//         strcat(line2, obj_str);
//
//         // 7. Display on LCD
//         LCD_SendCommand(0x80);       // Move to beginning of line 1
//         LCD_SendString("                "); // Clear line
//         LCD_SendCommand(0x80);       // Reset cursor
//         LCD_SendString(line1);
//
//         LCD_SendCommand(0xC0);       // Move to line 2
//         LCD_SendString("                "); // Clear line
//         LCD_SendCommand(0xC0);       // Reset cursor
//         LCD_SendString(line2);
//         // 8. Optional delay (basic debouncing / update rate)
//         for (volatile int i = 0; i < 300000; i++); // ~simple delay
//     }
//
//     return 0;
// }
//
