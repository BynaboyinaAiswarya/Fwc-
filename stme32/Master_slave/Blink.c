// GVV Sharma
// September 5, 2018
// Blink a LED using Timer1 as master and Timer2 as slave

#include <Arduino.h>

void setup() {
  // Enable GPIOA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  // Enable Timer1 and Timer2 clocks
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Timer1
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Timer2

  // Disable JTAG to free up PA15
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

  // Configure PA1 as output
  GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); // Clear PA1 settings
  GPIOA->CRL |= (GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1); // Output mode, max speed 50 MHz
  GPIOA->CRL &= ~GPIO_CRL_CNF1; // General purpose output push-pull

  // Configure Timer1 (Master)
  TIM1->SMCR = 0;             // Internal clock (8 MHz)
  TIM1->PSC = 0;              // No prescaler
  TIM1->ARR = 999;            // Auto-reload value
  TIM1->RCR = 0;              // No repetition
  TIM1->CR2 = 0x0020;         // MMS = 010 (Update event as TRGO)

  // Configure Timer2 (Slave)
  TIM2->PSC = 0;              // No prescaler
  TIM2->SMCR = 0x0007;        // TS = 000 (Internal trigger), SMS = 111 (Slave reset mode)
  TIM2->ARR = 999;            // Auto-reload value

  // Enable Timers
  TIM2->CR1 = 0x0001;         // Enable Timer2
  TIM1->CR1 = 0x0001;         // Enable Timer1
}

void loop() {
  // Check if Timer2 ARR count is complete
  if (TIM2->SR & 0x0001) {
    TIM2->SR &= ~0x0001;      // Clear Timer2 status register flag
    GPIOA->ODR ^= (1 << 1);   // Toggle PA1 (LED ON/OFF)
  }
}

