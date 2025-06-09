// GPIO.c

#include "GPIO.h"
#include "Bit_Operations.h"
#include "Utils.h"
#include "GPIO_Private.h"
#include "Std_Types.h"



// Available GPIO Ports
const GPIO_Port gpio_ports[] = {
    GPIO_PORT_INIT(GPIOA),
    GPIO_PORT_INIT(GPIOB),
    GPIO_PORT_INIT(GPIOC),
    GPIO_PORT_INIT(GPIOD)
};


// Get GPIO Port
const GPIO_RegDef *GetGpioPort(uint8 PortName) {

    for (uint8 i = 0; i < sizeof(gpio_ports)/sizeof(gpio_ports[0]); i++) {
        if (gpio_ports[i].PortName == PortName) {
            return &gpio_ports[i].Regs;
        }  // Just return address directly
    }
    return &gpio_ports[0].Regs; // Default to GPIOA
}




void GPIO_INIT(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState)
{
    const GPIO_RegDef *port = GetGpioPort(PortName);
    if (!port) return;

    // MODER Configuration
    *port->MODER &= ~(0x3 << (2 * PinNumber));
    *port->MODER |= (PinMode << (2 * PinNumber));

    if (PinMode == INPUT_MODE) {
        // PUPDR - Use pull-up for keypad columns
        *port->PUPDR &= ~(0x3 << (2 * PinNumber));
        *port->PUPDR |= (DefaultState << (2 * PinNumber));
    }
    else if (PinMode == OUTPUT_MODE) {
        // OTYPER
        *port->OTYPER &= ~(0x1 << PinNumber);
        *port->OTYPER |= ((DefaultState & 0x1) << PinNumber);

        // OSPEEDR - Critical fix! Set medium/high speed
        *port->OSPEEDR &= ~(0x3 << (2 * PinNumber));
        *port->OSPEEDR |= (0x2 << (2 * PinNumber));  // Medium speed
    }
}

void GPIO_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data)
{
    /* Get the GPIO port structure pointer */
    const GPIO_RegDef *port = GetGpioPort(PortName);

    /* Clear-then-set sequence (as requested) */
    *port->ODR &= ~(0x01 << PinNumber);      // 1. First clear the bit
    *port->ODR |= (Data << PinNumber); // 2. Then set new value

}
uint8 GPIO_ReadPin(uint8 PortName, uint8 PinNumber) {
    const GPIO_RegDef *port = GetGpioPort(PortName);
    return (*port->IDR >> PinNumber) & 0x1;
}

