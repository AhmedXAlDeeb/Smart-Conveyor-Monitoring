/*
 * ADC_private.h
 *
 *  Created on: Jun 4, 2025
 *      Author: Hassnaa Hossam
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include "../Lib/Utils.h"

#define ADC1_BASE_ADDR 			0x40012000
#define ADC_COMMON_BASE_ADDR 	0x40012300

typedef struct{
	volatile uint32 SR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SMPR1;
	volatile uint32 SMPR2;
	volatile uint32 JOFR1;
	volatile uint32 JOFR2;
	volatile uint32 JOFR3;
	volatile uint32 JOFR4;
	volatile uint32 HTR;
	volatile uint32 LTR;
	volatile uint32 SQR1;
	volatile uint32 SQR2;
	volatile uint32 SQR3;
	volatile uint32 JSQR;
	volatile uint32 JDR1;
	volatile uint32 JDR2;
	volatile uint32 JDR3;
	volatile uint32 JDR4;
	volatile uint32 DR;
}ADC_TYPE;

#define ADC1 				 ((ADC_TYPE *) ADC1_BASE_ADDR)
#define ADC_CCR 			 REG32(ADC_COMMON_BASE_ADDR + 0x04)


#endif /* ADC_PRIVATE_H_ */
