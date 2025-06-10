//
// Created by Lenovo on 18/04/2025.
//

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include "Rcc_Private.h"
#include "Rcc.h"

#include <stdint.h>

#define GPIO_NOPULL            0x0
#define GPIO_PULLUP            0x1
#define GPIO_PULLDOWN          0x2

// Port Name Definitions
#define GPIOA                  'A'
#define GPIOB                  'B'
#define GPIOC                  'C'
#define GPIOD                  'D'

// Modes
#define INPUT_MODE     0x0
#define OUTPUT_MODE    0x1
#define ALT_MODE       0x2
#define ANALOG_MODE    0x3

// Output Types
#define PUSH_PULL      0x0
#define OPEN_DRAIN     0x1

// Pull-Up/Pull-Down
#define NO_PULL        0x0
#define PULL_UP        0x1
#define PULL_DOWN      0x2

// Register Offsets
#define MODER_OFFSET    0x00
#define OTYPER_OFFSET   0x04
#define OSPEEDR_OFFSET  0x08
#define PUPDR_OFFSET    0x0C
#define IDR_OFFSET      0x10
#define ODR_OFFSET      0x14
#define BSRR_OFFSET     0x18
#define LCKR_OFFSET     0x1C
#define AFRL_OFFSET     0x20
#define AFRH_OFFSET     0x24

// Base Addresses (STM32F4 example)
#define GPIOA_BASE_ADDR   0x40020000
#define GPIOB_BASE_ADDR   0x40020400
#define GPIOC_BASE_ADDR   0x40020800
#define GPIOD_BASE_ADDR   0x40020C00

// Register access macro
// #define REG32(addr) (*(volatile uint32_t *)(addr))


// GPIO Register Structure
typedef struct {
    volatile uint32 *MODER;
    volatile uint32 *OTYPER;
    volatile uint32 *OSPEEDR;
    volatile uint32 *PUPDR;
    volatile uint32 *IDR;
    volatile uint32 *ODR;
    volatile uint32 *BSRR;
    volatile uint32 *LCKR;     // Configuration lock register (optional but standard)
    volatile uint32 *AFRL;     // Alternate function low register (pins 0–7)
    volatile uint32 *AFRH;     // Alternate function high register (pins 8–15)
} GPIO_RegDef;

// they are seperated as we may need change the registers used in a specific GPIO or we may not use
// the same registers in all the gpios

#define GPIO_REG(REG_ID, PORT_ID) ((volatile uint32*)((PORT_ID) + (REG_ID)))


// Macro to initialize GPIO registers
// Rather than removing the GPIO addresses written in the .h file we can make use of them by utalizing this macro
// it takes input the port name and define a nested struct
// the ## opertator is used in concatenation of parts and replacement
#define GPIO_PORT_INIT(port) \
{ port, \
{ (volatile uint32*)(port##_BASE_ADDR + MODER_OFFSET),   \
(volatile uint32*)(port##_BASE_ADDR + OTYPER_OFFSET),  \
(volatile uint32*)(port##_BASE_ADDR + OSPEEDR_OFFSET), \
(volatile uint32*)(port##_BASE_ADDR + PUPDR_OFFSET),   \
(volatile uint32*)(port##_BASE_ADDR + IDR_OFFSET),     \
(volatile uint32*)(port##_BASE_ADDR + ODR_OFFSET),     \
(volatile uint32*)(port##_BASE_ADDR + BSRR_OFFSET),    \
(volatile uint32*)(port##_BASE_ADDR + LCKR_OFFSET),    \
(volatile uint32*)(port##_BASE_ADDR + AFRL_OFFSET),    \
(volatile uint32*)(port##_BASE_ADDR + AFRH_OFFSET)     \
} \
}

#endif //GPIO_PRIVATE_H
