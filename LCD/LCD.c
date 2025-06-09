#include "LCD.h"
#include "GPIO.h"
#include "GPIO_Private.h"
#include "Std_Types.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// Internal buffers to track last written lines
static char lcd_prev_line1[17] = "                ";
static char lcd_prev_line2[17] = "                ";

static void LCD_EnablePulse(void);
static void LCD_Write4Bits(uint8 nibble);

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

static void LCD_Write4Bits(uint8 nibble) {
    GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (nibble >> 0) & 0x1);
    GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (nibble >> 1) & 0x1);
    GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (nibble >> 2) & 0x1);
    GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (nibble >> 3) & 0x1);
    LCD_EnablePulse();
}

static void LCD_Send(uint8 data, uint8 rs) {
    GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, rs);
    LCD_Write4Bits(data >> 4);
    LCD_Write4Bits(data & 0x0F);
    lcd_delay_ms(2);
}

void LCD_SendCommand(uint8 cmd) {
    LCD_Send(cmd, 0);
}

void LCD_SendData(uint8 data) {
    LCD_Send(data, 1);
}

void LCD_Init(void) {
    GPIO_INIT(LCD_RS_PORT, LCD_RS_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_EN_PORT, LCD_EN_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D4_PORT, LCD_D4_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D5_PORT, LCD_D5_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D6_PORT, LCD_D6_PIN, OUTPUT_MODE, PUSH_PULL);
    GPIO_INIT(LCD_D7_PORT, LCD_D7_PIN, OUTPUT_MODE, PUSH_PULL);

    lcd_delay_ms(40);
    LCD_Write4Bits(0x03); lcd_delay_ms(2);
    LCD_Write4Bits(0x03); lcd_delay_ms(1);
    LCD_Write4Bits(0x03); lcd_delay_ms(1);
    LCD_Write4Bits(0x02); lcd_delay_ms(1);

    LCD_SendCommand(LCD_CMD_FUNCTION_SET);
    LCD_SendCommand(LCD_CMD_DISPLAY_ON);
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    lcd_delay_ms(2);
    LCD_SendCommand(LCD_CMD_ENTRY_MODE);
}

void LCD_SendString(const char *str) {
    while (*str) {
        LCD_SendData((uint8)*str++);
    }
}

void LCD_SetCursor(uint8 row, uint8 col) {
    uint8 address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_SendCommand(address);
}

// New function: smart update of a line
void LCD_UpdateLine(uint8 row, const char *new_line) {
    char *prev_line = (row == 0) ? lcd_prev_line1 : lcd_prev_line2;
    for (uint8 i = 0; i < 16; ++i) {
        char new_char = (i < strlen(new_line)) ? new_line[i] : ' ';
        if (new_char != prev_line[i]) {
            LCD_SetCursor(row, i);
            LCD_SendData(new_char);
            prev_line[i] = new_char;
        }
    }
}
