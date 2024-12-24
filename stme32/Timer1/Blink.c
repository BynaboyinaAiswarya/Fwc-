
// GVV Sharma
// August 31, 2018
// Blink an LED using HSI clock and Timer1

#include <Arduino.h>

void setup() {
  // Enable GPIOA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  // Enable Timer1 clock
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

  // Disable JTAG to free up PA15
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

  // Configure PA1 as output
  GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); // Clear PA1 settings
  GPIOA->CRL |= (GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1); // Output mode, max speed 50 MHz
  GPIOA->CRL &= ~GPIO_CRL_CNF1; // General purpose output push-pull

  // Configure Timer1
  TIM1->SMCR = 0;                // Internal clock (8 MHz)
  TIM1->PSC = 999;               // Prescaler: Divide clock by 1000
  TIM1->ARR = 999;               // Auto-reload register value
  TIM1->RCR = 3;                 // Repetition counter
  TIM1->CR1 = 0x0001;            // Enable Timer1
}

void loop() {
  // Check if the timer reached the ARR value
  if (TIM1->SR & 0x0001) {
    TIM1->SR &= ~0x0001;         // Clear the status register flag
    GPIOA->ODR ^= (1 << 1);      // Toggle PA1 (LED ON/OFF)
  }
}
