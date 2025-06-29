/*
 * ADC_interface.c
 *
 *  Created on: Jun 4, 2025
 *      Author: Hassnaa Hossam
 */

#ifndef ADC_INTERFACE_C_
#define ADC_INTERFACE_C_

#include <../Lib/Std_Types.h>

// prescaler
#define ADC_PRESCALER_2										0X0
#define ADC_PRESCALER_4										0X1
#define ADC_PRESCALER_6										0X2
#define ADC_PRESCALER_8										0X3

// Resolutions 12, 10, 8, 6
#define ADC_RESOLUTION_12_BIT								0x0
#define ADC_RESOLUTION_10_BIT								0x1
#define ADC_RESOLUTION_8_BIT								0x2
#define ADC_RESOLUTION_6_BIT								0x3

// Alignment
#define ADC_RIGHT_ALIGNMENT									0X0
#define ADC_LEFT_ALIGNMENT									0X1

// Sampling rate
#define ADC_3_CYCLES										0X0
#define ADC_15_CYCLES										0X1
#define ADC_28_CYCLES										0X2
#define ADC_56_CYCLES										0X3
#define ADC_84_CYCLES										0X4
#define ADC_112_CYCLES										0X5
#define ADC_144_CYCLES										0X6
#define ADC_480_CYCLES										0X7

// ADC Channel mode single / multi, single / continuous, discontinuous
#define ADC_SINGLE_CHANNEL_SINGLE_CONVERSION_MODE 			1
#define ADC_SINGLE_CHANNEL_CONTINUOUS_CONVERSION_MODE 		2
#define ADC_MULTI_CHANNEL_SINGLE_CONVERSION_MODE 			3
#define ADC_MULTI_CHANNEL_CONTINUOUS_CONVERSION_MODE 		4
#define ADC_DISCONTINUOUS_CONVERSION_MODE					5


void ADC_Init(uint8 port, uint8 channel);
uint16 ADC_Conversion(void);

#endif /* ADC_INTERFACE_C_ */
