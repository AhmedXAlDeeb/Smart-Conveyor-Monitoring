
#include <stdlib.h>
#include <string.h>
#include "../RCC/Rcc.h"
#include "../GPIO/GPIO.h"
#include "../LCD/LCD.h"
#include "../ADC/ADC_interface.h"
#include "../ADC/ADC_private.h"
#include "Std_Types.h"
#include "../EXTI/EXIT_interface.h"

// PINS DEFINE
#define LED_PIN1    11 // Red
#define LED_PIN2    13 // Green
#define LED_PIN3    15 // Blue
#define PUSH_BUTTON_PIN 3
#define  BUTTON_PIN       0

// #include "stm32f4xx.h"

// typedef struct {
//     uint32 IMR;
//     uint32 EMR;
//     uint32 RTSR;
//     uint32 FTSR;
//     uint32 SWIER;
//     uint32 PR;
// } ExtiType;
//
// typedef struct {
//     uint32 NVIC_ISER[8];
//     uint32 NVIC_ICER[8];
// }NVICType;
//
//
// #define EXTI ((volatile ExtiType*) 0x40013C00)
//
// #define NVIC  ((NVICType*)0xE000E100)

int main() {
    // 1. Enable the GPIOA clock (assuming LCD is connected to GPIOA)
    RCC_AHB1ENR |= (1 << 0);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 1);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 2);  // Enable clock for GPIOA
    Rcc_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_ADC1);
    // Rcc_Enable(RCC_SYSCFG);
    GPIO_INIT('B', 0, INPUT_MODE, PULL_UP);
    GPIO_INIT('B', 2, OUTPUT_MODE, PUSH_PULL);

    EXTI_Init(BUTTON_PIN, GPIOB, FALLING_TRIGGER);
    EXTI_Enable(BUTTON_PIN);

    // SYSCFG->EXTICR[0] &= ~(0x0F <<(0 * 4));
    // SYSCFG->EXTICR[0] |= (0x01 <<(0 * 4));
    //
    // EXTI->FTSR |= (0X01 << 0);   //enable falling edge on E0
    //
    // NVIC->NVIC_ISER[0] |= (0x01 << 6); //enable line 6 interrupt E0
    // EXTI->IMR |= (0x01 << 0);   //enable interrupt mask register

    // initialize ADC channel 1
    ADC_Init('A', 1);

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

    while (1) {
        uint16 pot_value = ADC_Conversion();
        /// for testing pot value
        //    	itoa(pot_value, motor_str, 10);
        //    	strcpy(line1, "M:");
        //    	strcat(line1, motor_str);
        //    	LCD_SendCommand(0x01);       // Clear display
        //    	LCD_SendString(line1);       // First line
    }

    return 0;
}

uint8 t =0;
void EXTI0_IRQHandler(void) {
    t= !t;
    GPIO_WritePin('B', 2, t);
}
