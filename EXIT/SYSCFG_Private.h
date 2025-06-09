//
// Created by EMAN on 6/9/2025.
//
#ifndef SYSCFG_PRIVATE_H
#define SYSCFG_PRIVATE_H

#define SYSCFG ((SYSCFG_TypeDef *) 0x40013800)

typedef struct {
    volatile uint32 MEMRMP;
    volatile uint32 PMC;
    volatile uint32 EXTICR[4];
    volatile uint32 RESERVED[2];
    volatile uint32 CMPCR;
} SYSCFG_TypeDef;

#endif //SYSCFG_PRIVATE_H