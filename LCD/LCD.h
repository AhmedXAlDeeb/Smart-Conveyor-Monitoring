#ifndef LCD_H
#define LCD_H

#include "../Lib/Std_Types.h"
#include "GPIO.h"

// === LCD Control Pins Configuration ===
#define LCD_RS_PORT   GPIOB
#define LCD_RS_PIN    4

#define LCD_EN_PORT   GPIOB
#define LCD_EN_PIN    5   // EN pin at PB9



// LCD Data Pins D4 - D7 mapped to PB4 - PB7
#define LCD_D4_PORT   GPIOB
#define LCD_D4_PIN    6

#define LCD_D5_PORT   GPIOB
#define LCD_D5_PIN    7

#define LCD_D6_PORT   GPIOB
#define LCD_D6_PIN    8

#define LCD_D7_PORT   GPIOB
#define LCD_D7_PIN    9

// === LCD Commands ===
#define LCD_CMD_CLEAR_DISPLAY     0x01
#define LCD_CMD_RETURN_HOME       0x02
#define LCD_CMD_ENTRY_MODE        0x06
#define LCD_CMD_DISPLAY_ON        0x0C
#define LCD_CMD_FUNCTION_SET      0x28  // 4-bit mode, 2 lines, 5x8 font
#define LCD_CMD_SET_CURSOR_LINE2  0xC0

// === Public LCD API ===
void LCD_Init(void);
void LCD_SendCommand(uint8 cmd);
void LCD_SendChar(uint8 data);
void LCD_SendString(const char* str);

#endif // LCD_H
