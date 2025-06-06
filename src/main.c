#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LCD.h"
#include "Rcc.h"
#include "Std_Types.h"
#include "ADC_interface.h"
#include "../EXTI/EXIT_interface.h"

// PORTS BASE ADDRESS (STM32F401 specific)
#define GPIOB_BASE_ADDRESS 0x40020400 // GPIOB base address
#define GPIOA_BASE_ADDRESS 0x40020000 // GPIOA base address
#define GPIOC_BASE_ADDRESS 0x40020800 // GPIOC base address
#define RCC_BASE_ADDRESS   0x40023800 // RCC base address

// REGISTERS OFFSETS FROM THE BASE
#define MODER_OFFSET    0x00
#define OTYPER_OFFSET   0x04
#define OSPEEDR_OFFSET  0x08
#define PUPDR_OFFSET    0x0C
#define IDR_OFFSET      0x10
#define ODR_OFFSET      0x14
#define RCC_AHB1ENR_OFFSET 0x30 // RCC AHB1ENR offset
#define RCC_APB1ENR_OFFSET 0x40 // RCC APB1ENR offset (for TIM2)

// GPIO REGISTERS ADDRESS
#define GPIOA_MODER     (*(unsigned long *)(GPIOA_BASE_ADDRESS + MODER_OFFSET))
#define GPIOA_OTYPER    (*(unsigned long *)(GPIOA_BASE_ADDRESS + OTYPER_OFFSET))
#define GPIOA_PUPDR     (*(unsigned long *)(GPIOA_BASE_ADDRESS + PUPDR_OFFSET))
#define GPIOA_IDR       (*(unsigned long *)(GPIOA_BASE_ADDRESS + IDR_OFFSET))

#define GPIOC_MODER     (*(unsigned long *)(GPIOC_BASE_ADDRESS + MODER_OFFSET))
#define GPIOC_OTYPER    (*(unsigned long *)(GPIOC_BASE_ADDRESS + OTYPER_OFFSET))
#define GPIOC_OSPEEDR   (*(unsigned long *)(GPIOC_BASE_ADDRESS + OSPEEDR_OFFSET))
#define GPIOC_ODR       (*(unsigned long *)(GPIOC_BASE_ADDRESS + ODR_OFFSET))

// RCC
#define RCC_AHB1ENR     (*(unsigned long *)(RCC_BASE_ADDRESS + RCC_AHB1ENR_OFFSET))
#define RCC_APB1ENR     (*(unsigned long *)(RCC_BASE_ADDRESS + RCC_APB1ENR_OFFSET))

// TIM2 REGISTERS
#define TIM2_BASE_ADDRESS 0x40000000 // TIM2 base address
#define TIM2_CR1    (*(unsigned long *)(TIM2_BASE_ADDRESS + 0x00)) // Control register 1
#define TIM2_CNT    (*(unsigned long *)(TIM2_BASE_ADDRESS + 0x24)) // Counter
#define TIM2_PSC    (*(unsigned long *)(TIM2_BASE_ADDRESS + 0x28)) // Prescaler
#define TIM2_ARR    (*(unsigned long *)(TIM2_BASE_ADDRESS + 0x2C)) // Auto-reload register

// PINS DEFINE
#define LED_PIN1    11 // Red
#define LED_PIN2    13 // Green
#define LED_PIN3    15 // Blue
#define PUSH_BUTTON_PIN 3

const int colors[8] = {0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07};

// Assuming 16 MHz system clock (HSI default for STM32F401)
// APB1 clock = 16 MHz (no prescaler in default configuration)
// Adjust PRESCALER if using PLL (e.g., APB1 at 42 MHz for 84 MHz system clock)

#define  APB1_CLOCK    16000000
#define  PRESCALER     16              // Prescaler to get 1 MHz timer clock (16 MHz / 16 = 1 MHz)
#define  TICKS_PER_MS  1000            // 1 MHz / 1000 = 1 kHz (1 ms per tick)
#define  BUTTON_PIN       0

void TIM2_Init(void) {
    // Enable TIM2 clock
    RCC_APB1ENR |= (1 << 0);       // Enable TIM2 in APB1

    // Configure TIM2
    TIM2_PSC = PRESCALER - 1;    // Set prescaler (e.g., 16 MHz / 16 = 1 MHz)
    TIM2_ARR = 0xFFFFFFFF;       // Set max auto-reload for 32-bit timer
    TIM2_CR1 |= (1 << 0);           // Enable timer (CEN bit)
}

void delayy(unsigned int ms) {

    TIM2_CNT = 0;       // Reset counter
    unsigned long target = ms * TICKS_PER_MS;      // Target count for ms delay
    while (TIM2_CNT < target) {
        // Wait
    }  }

unsigned char last_button_state = 1; // Default is not pressed (pull-up)

int is_button_pressed() {
    // Apply debouncing effect
    unsigned char current_state1 = 1, current_state2 = 1;
    current_state1 = (GPIOA_IDR & (1 << PUSH_BUTTON_PIN)) ? 0 : 1;
    delayy(30);
    current_state2 = (GPIOA_IDR & (1 << PUSH_BUTTON_PIN)) ? 0 : 1;

    if (current_state1 == 1 && current_state2 == 1) {
        if (last_button_state == 0) {
            last_button_state = 1;
            return 1;
        }
    }
    last_button_state = current_state1;
    return 0;
}
void set_led_color(int color) {
    // Clear all LED pins
    GPIOC_ODR &= ~(1 << LED_PIN1);
    GPIOC_ODR &= ~(1 << LED_PIN2);
    GPIOC_ODR &= ~(1 << LED_PIN3);

    // Set each pin based on color value
    if (color & 0x01) GPIOC_ODR |= (1 << LED_PIN1);
    if (color & 0x02) GPIOC_ODR |= (1 << LED_PIN2);
    if (color & 0x04) GPIOC_ODR |= (1 << LED_PIN3);
}
int main() {
    // 1. Enable the GPIOA clock (assuming LCD is connected to GPIOA)
    RCC_AHB1ENR |= (1 << 0);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 1);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 2);  // Enable clock for GPIOA
    Rcc_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_ADC1);
    Rcc_Enable(RCC_SYSCFG);
    GPIO_INIT('B', 0, INPUT_MODE, PULL_UP);
    // GPIO_INIT('B', 2, OUTPUT_MODE, PUSH_PULL);

    EXTI_Init(BUTTON_PIN, GPIOB, FALLING_TRIGGER);
    EXTI_Enable(BUTTON_PIN);

    ADC_Init('A', 1);   // initialize ADC channel 1

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

// uint8 t =1; 

// function to be implemented when emergency
void EXTI0_IRQHandler(void) {
    // GPIO_WritePin('B', 2, t);
}
