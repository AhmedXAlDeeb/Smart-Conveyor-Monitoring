//
// Created by EMAN on 6/6/2025.
//
#include "EXIT_interface.h"

#include <../LIB/Std_Types.h>
#include "../GPIO/GPIO.h"

#include "../GPIO/GPIO_Private.h"
#include "STM32F4xx.h"
#define NVIC     ((volatile NVICType*) (0xE000E100))



void EXTI_Init( uint8 pin ,uint8 Port , uint8 trigger) {
    uint8_t reg_index = pin / 4;
    SYSCFG->EXTICR[reg_index] &=~(0x0f<<((pin % 4)*4));

    if (Port == GPIOA) {
        SYSCFG->EXTICR[reg_index] |=(interrupt_portA_code<<((pin % 4)*4));
    }else if (Port == GPIOB) {
        SYSCFG->EXTICR[reg_index] |=(interrupt_portB_code<<((pin % 4)*4));
    }else if (Port == GPIOC) {
        SYSCFG->EXTICR[reg_index] |=(interrupt_portC_code<<((pin % 4)*4));
    }
    else {
        SYSCFG->EXTICR[reg_index] |=(interrupt_portD_code<<((pin % 4)*4));
    }
    // switch (Port){
    //     case GPIOA:
    //         SYSCFG->EXTICR[reg_index] |=(interrupt_portA_code<<((pin % 4)*4));
    //     break;
    //     case GPIOB:
    //         SYSCFG->EXTICR[reg_index] |=(interrupt_portB_code<<((pin % 4)*4));
    //     break;
    //     case GPIOC:
    //         SYSCFG->EXTICR[reg_index] |=(interrupt_portC_code<<((pin % 4)*4));
    //     break;
    //     case GPIOD:
    //         SYSCFG->EXTICR[reg_index] |=(interrupt_portD_code<<((pin % 4)*4));
    //     break;
    // }
    EXTI->RTSR &= ~(1 << pin);
    EXTI->FTSR &= ~(1 << pin);
    if (trigger==RISING_TRIGGER) {
        EXTI->RTSR |=(0x1<<pin);
    }else if (trigger==FALLING_TRIGGER) {
        EXTI->FTSR |=(0x1<<pin);
    }else if (trigger==RISING_AND_FALLING_TRIGGER) {
        EXTI->RTSR |= (0x1 << pin);
        EXTI->FTSR |= (0x1 << pin);
    }

}

void EXTI_Enable(uint8 pin) {
    EXTI->IMR |= (0x01<<pin);
    uint8_t irq_num = EXTI_GetIRQn(pin);
    NVIC->NVIC_ISER[irq_num / 32] |= (0x01 << (irq_num % 32));
}

void EXTI_Disable(uint8 pin) {
    EXTI->IMR &= ~(1 << pin);
    uint8_t irq_num = EXTI_GetIRQn(pin);
    NVIC->NVIC_ICER[irq_num / 32] |= (1 << (irq_num % 32));
}


uint8 EXTI_GetIRQn(uint8 pin) {
    if (pin <= 4)
        return 6 + pin;
    else if (pin <= 9)
        return 23;
    else
        return 40;
}
