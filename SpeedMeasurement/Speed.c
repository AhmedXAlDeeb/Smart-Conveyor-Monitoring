//
// Created by Mohamed Yasser on 6/6/2025.
//

#include "Speed.h"
#include "stm32f4xx.h"

void SpeedMeasurement_Init(void) {
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // PA0 -> TIM2_CH1
  GPIOA->MODER &= ~(3 << (0 * 2));
  GPIOA->MODER |=  (2 << (0 * 2));     // Alternate function
  GPIOA->AFR[0] &= ~(0xF << (0 * 4));
  GPIOA->AFR[0] |=  (1 << (0 * 4));    // AF1 = TIM2_CH1

  TIM2->PSC = 84 - 1;                  // Prescaler → 1MHz tick
  TIM2->CCMR1 = 0x01;                  // CC1 channel is input, mapped to TI1
  TIM2->CCER &= ~(1 << 1);             // Rising edge
  TIM2->CCER |= 1;                     // Enable capture
  TIM2->CR1 |= 1;                      // Enable counter
}


float Get_SignalFrequency(void) {
  TIM2->CNT = 0;
  TIM2->SR &= ~TIM_SR_CC1IF;  // Clear flag

  int timeout = 1000000;  // Adjust as needed

  // Wait for 1st edge
  while (!(TIM2->SR & TIM_SR_CC1IF) && timeout--);
  if (timeout <= 0) return 0;

  uint32_t t1 = TIM2->CCR1;
  TIM2->SR &= ~TIM_SR_CC1IF;

  timeout = 1000000; // Reset timeout
  while (!(TIM2->SR & TIM_SR_CC1IF) && timeout--);
  if (timeout <= 0) return 0;

  uint32_t t2 = TIM2->CCR1;
  TIM2->SR &= ~TIM_SR_CC1IF;

  if (t2 > t1) {
    uint32_t delta = t2 - t1;
    float period_sec = delta / 1000000.0f;  // 1 MHz timer
    return 1.0f / period_sec;  // Frequency = 1 / period
  }

  return 0;
}
