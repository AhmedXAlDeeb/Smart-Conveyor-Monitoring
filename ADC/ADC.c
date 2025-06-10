/*
 * ADC.c
 *
 *  Created on: Jun 4, 2025
 *      Author: Hassnaa Hossam
 */

#include "../GPIO/GPIO.h"
#include "../Lib/Std_Types.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"


void ADC_Init(uint8 port, uint8 channel){
	// initialize GPIO pin as analog
	GPIO_INIT(port, channel, ANALOG_MODE, NO_PULL);

	// prescaler in ADC_CCR (2 bits: 16, 17)
	ADC_CCR &= ~(0x3 << 16);
	ADC_CCR |=  ((ADC_PRESCALER & 0x3) << 16);

	// Disable ADC by clear ADON bit in ADC_CR2 (bit: 0)
	ADC1->CR2 &= ~(0x1 << 0);

	// resolution in ADC_CR1 (2 bits: 24, 25)
	ADC1->CR1 &= ~(0x3 << 24);
	ADC1->CR1 |=  ((ADC_RESOLUTION & 0x3) << 24);

	// Data Alignment in ADC_CR2 (bit: 11)
	ADC1->CR2 &= ~(0x1 << 11);
	ADC1->CR2 |=  (ADC_DATA_ALIGNMENT << 11);

	//  Bit 1 CONT: Continuous conversion Bit
	ADC1->CR2 &= ~(0x1 << 1);
	ADC1->CR2 |= (ADC_SINGLE_CONT << 1);

	// Bit 10 EOCS: End of conversion selection
	ADC1->CR2 |= (0x1 << 10); // EOC is set at the end of each individual conversion.

	// sampling rate: SAMPLING_RATE * ADC Clock
	// The ADC will spend "SAMPLING_RATE value" ADC clock cycles sampling the input signal before starting the conversion.
	if (channel <= 9){ // Channels 0–9: configured in SMPR2
		ADC1->SMPR2 &= ~(0x7 << (channel * 3));
		ADC1->SMPR2 |= (SAMPLING_RATE << (channel * 3));
	} else{ // Channels 10–18: configured in SMPR1
		ADC1->SMPR1 &= ~(0x7 << ((channel - 10) * 3));
		ADC1->SMPR1 |= (SAMPLING_RATE << ((channel - 10) * 3));
	}

	// Enable/Disable interrupt after conversion for regular mode in ADC_CR1 register EOCIE Bit (bit: 5)
	ADC1->CR1 &= ~(0x1 << 5);
	ADC1->CR1 |=  (ADC_INTERRUPT_MODE << 5);

	// length in ADC_SQR1 register (bits: 20, 21, 22, 23)
	ADC1->SQR1 &= ~(0xF << 20);  // length = 1 only one channel
	ADC1->SQR1 |=  ((NUM_CHANNELS - 1) << 20);

	// Set channel in SQ1
	ADC1->SQR3 &= ~(0x1F << 0); // 0 for first sequence
	ADC1->SQR3 |=  (channel  << 0);

	// Enable ADC by set ADON bit in ADC_CR2 (bit: 0)
	ADC1->CR2 |=  (0x1 << 0);
}

uint16 ADC_Conversion() {
	// Bit 30 SWSTART in CR2: Start conversion of regular channels
    ADC1->CR2 |= (1 << 30);

	while (!((ADC1->SR >> 1) & 0x1));  // Wait for EOC flag

    // Read data from DR
    return ADC1->DR;
}
