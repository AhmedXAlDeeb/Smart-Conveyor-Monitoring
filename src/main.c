#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdint.h"
#include "cmsis_gcc.h"
#include "../Delay/Delay.h"
#include "../RCC/Rcc.h"
#include "../GPIO/GPIO.h"
#include "../LCD/LCD.h"
#include "../ADC/ADC_interface.h"
#include "../PWM/PWM.h"
#include "../EXTI/EXTI_interface.h"


#define pot_pin  		1
#define IR_button_pin  	1
#define emergency_pin   4
#define emergency_LED   3

uint8 emergency_flag = 0;      // 0: normal, 1: emergency
void emergency_func(void);

int main(void) {
    // 1. Enable the GPIOA clock (assuming LCD is connected to GPIOA)
    RCC_AHB1ENR |= (1 << 0);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 1);  // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 2);  // Enable clock for GPIOA
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_ADC1);
    Rcc_Enable(RCC_SYSCFG);

    // initialize ADC channel 1
    ADC_Init(GPIOA, pot_pin);

	// 2. Initialize the LCD
    LCD_Init();

    // Initialize interrupt pin
    GPIO_INIT(GPIOA, emergency_LED, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(GPIOA, emergency_pin, INPUT_MODE, PULL_UP);
    GPIO_INIT(GPIOA, 8, OUTPUT_MODE, PUSH_PULL);
//    EXTI_Init(emergency_pin, GPIOA, RISING_TRIGGER);
    //    EXTI_Enable(emergency_pin);
    Exti_Init(EXTI_LINE_4, EXTI_PORT_A, EXTI_EDGE_RISING, emergency_func);
    Exti_Enable(EXTI_LINE_4);

	// Initialize GPIO button PB1 simulating IR sensor for object detection
	GPIO_INIT(GPIOB, IR_button_pin, INPUT_MODE, PULL_UP);

	// Initialize PWM pin PA9 = TIM1_CH2
    PWM_Init(2);
    PWM_Start();
    // Set PB0 and PB1 as output push-pull
    GPIO_INIT('B', 2, OUTPUT_MODE, PUSH_PULL);  // PB0
    GPIO_INIT('B', 3, OUTPUT_MODE, PUSH_PULL);  // PB1

    // Optional: Set initial value
    GPIO_WritePin('B', 2, 1);  // Set PB0 HIGH
    GPIO_WritePin('B', 3, 0);  // Set PB1 LOW


    char line1[17] = {0};
    char line2[17] = {0};

    char motor_str[8];
    char conv_str[8];
    char obj_str[6];

    uint16 conveyor_speed = 0;
	uint32 object_count = 0;
	uint16 previous_ir_state = 1;
    while (1) {
//    	EXTI_Disable(emergency_pin);
        uint16 pot_value = ADC_Conversion();  // Range 0–4095

        // Calculate motor speed
        uint32 motor_speed = ((uint32)pot_value * 100U) / 4095U;

        // Set PWM
        PWM_SetDutyCycle((uint16)motor_speed);

		// Object Detection polling on falling edge
		uint16 curr_ir_state = GPIO_ReadPin(GPIOB, IR_button_pin);
		if(previous_ir_state == 1 && curr_ir_state == 0){
			object_count += 1;
		}
		previous_ir_state = curr_ir_state;  // update previous value
//		EXTI_Enable(emergency_pin);
		if (emergency_flag == 0){
			itoa(motor_speed, motor_str, 10);
			itoa(pot_value, conv_str, 10);
			itoa(object_count, obj_str, 10);

			// line1 = "M:<motor>% C:<conveyor>"
			strcpy(line1, "M:");
			strcat(line1, motor_str);
			strcat(line1, "% C:");
			strcat(line1, conv_str);

			// line2 = "Obj:<object_count>"
			strcpy(line2, "Obj:");
			strcat(line2, obj_str);

			LCD_UpdateLine(0, line1);  // Update row 0 with line1
			LCD_UpdateLine(1, line2);  // Update row 1 with line2
		}else if(emergency_flag == 1){
			strcpy(line1, "EMERGENCY STOP");
			strcpy(line2, "");
		    LCD_UpdateLine(0, line1);  // Update row 0 with line1
		    LCD_UpdateLine(1, line2);  // Update row 1 with line2

		}
//        delay_ms(50);  // Small delay

    }
    return 0;
}


void emergency_func(void) {
    __disable_irq();
	emergency_flag = 1;
	GPIO_WritePin(GPIOA, emergency_LED, 1);
    __enable_irq();
}
