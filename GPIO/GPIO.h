// GPIO.h

#ifndef GPIO_H
#define GPIO_H
#include "GPIO_private.h"
#include "../Lib/Std_Types.h"

typedef enum {
    E_NOT_OK = 0,
    E_OK = 1
} Std_ReturnType;


// Combines port identification with its hardware registers
typedef struct {
    uint8 PortName;
    GPIO_RegDef Regs;
} GPIO_Port;

void GPIO_INIT(uint8 port_name, uint8 pin_number, uint8 mode, uint8 default_state);

void GPIO_WritePin(uint8 portNam, uint8 pinNumber, uint8 data);

uint8 GPIO_ReadPin(uint8 portNam, uint8 pinNumber);

#endif /* GPIO_H */