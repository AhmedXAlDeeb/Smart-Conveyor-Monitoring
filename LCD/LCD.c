//
// Created by Lenovo on 02/06/2025.
//
#include "LCD.h"
#include "GPIO.h"
#include "GPIO_Private.h"
#include "Std_Types.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>    // for uint8_t, uint32_t (if Std_Types.h doesn't already)


// Only these two static helpers need declarations:
static void LCD_EnablePulse(void);
static void LCD_Write4Bits(uint8_t nibble);

// Simple loop‐based millisecond delay
static void lcd_delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        for (volatile uint32_t j = 0; j < 8000; j++);
    }
}

static void LCD_EnablePulse(void) {
    GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, 1);
    lcd_delay_ms(1);
    GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, 0);
    lcd_delay_ms(1);
}

static void LCD_Write4Bits(uint8_t nibble) {
    GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (nibble >> 0) & 0x1);
    GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (nibble >> 1) & 0x1);
    GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (nibble >> 2) & 0x1);
    GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (nibble >> 3) & 0x1);
    LCD_EnablePulse();
}

// Sends either a command (rs=0) or data (rs=1) in two 4‐bit halves
static void LCD_Send(uint8_t data, uint8_t rs) {
    GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, rs);
    LCD_Write4Bits(data >> 4);      // high nibble
    LCD_Write4Bits(data & 0x0F);    // low nibble
    lcd_delay_ms(2);
}

void LCD_SendCommand(uint8_t cmd) {
    LCD_Send(cmd, 0);
}

void LCD_SendData(uint8_t data) {
    LCD_Send(data, 1);
}

void LCD_Init(void) {
    // Initialize control + data pins as outputs
    GPIO_INIT(LCD_RS_PORT, LCD_RS_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_EN_PORT, LCD_EN_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D4_PORT, LCD_D4_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D5_PORT, LCD_D5_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D6_PORT, LCD_D6_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D7_PORT, LCD_D7_PIN, OUTPUT_MODE, PUSH_PULL);

    lcd_delay_ms(40); // Wait >40ms after power‐up

    // The “wake up” sequence for 4‐bit mode
    LCD_Write4Bits(0x03);
    lcd_delay_ms(5);
    LCD_Write4Bits(0x03);
    lcd_delay_ms(1);
    LCD_Write4Bits(0x03);
    LCD_Write4Bits(0x02);  // Now in 4‐bit mode

    // Function set: 4‐bit, 2-line, 5×8 dots
    LCD_SendCommand(LCD_CMD_FUNCTION_SET);
    // Display ON, cursor OFF
    LCD_SendCommand(LCD_CMD_DISPLAY_ON);
    // Clear display
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    lcd_delay_ms(2);
    // Entry mode: increment, no shift
    LCD_SendCommand(LCD_CMD_ENTRY_MODE);
}

void LCD_SendString(const char *str) {
    while (*str) {
        LCD_SendData((uint8_t)*str++);
    }
}
