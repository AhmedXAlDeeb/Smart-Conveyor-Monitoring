
/**
 * Keypad.h
 *
 *  Created on: Thu Apr 27 2023
 *  Author    : Abdullah Darwish
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include "Gpio.h"

#define COL_PORT  GPIOA
#define COL_START_INDEX 0
#define COL_END_INDEX 2

#define ROW_PORT GPIOB
#define ROW_START_INDEX 4
#define ROW_END_INDEX 7

#define HIGH 1
#define LOW 0

#define ROW_COUNT  4
#define COL_COUNT  3


typedef struct {
    char PortName;
    uint8 PinNum;
} GpioPin;


typedef struct {
    GpioPin rowPins[ROW_COUNT];
    GpioPin colPins[COL_COUNT];
    const uint8 *keymap;
} KeypadConfig;



// provided api functions
void KEYPAD_INIT(void);

void KEYPAD_MANAGE(void);

char KEYPAD_GETKEY(void);


// required function implemented by applicaiton
void KeypadCallout_KeyPressNotificaton();


#endif /* KEYPAD_H */
