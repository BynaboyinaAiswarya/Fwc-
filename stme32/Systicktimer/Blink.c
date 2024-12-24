
// GVV Sharma
// August 24, 2018
// Blink an LED using HSI clock and SysTick timer

#include <Arduino.h>

void delay_us(uint32_t time) {
  // Load the delay period in microseconds
  SysTick->LOAD = time;
  // Clears the current value and the count flag
  SysTick->VAL = 0;
  
  // Wait until the count ends
  while (!(SysTick->CTRL & 0x00010000)); // Wait for COUNTFLAG
}

void setup() {
  // Enable GPIOA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  // Disable JTAG and SWO to free PA15
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

  // Configure PA1 as a digital output
  GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); // Clear PA1 settings
  GPIOA->CRL |= (GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1); // Output mode, max speed 50 MHz
  GPIOA->CRL &= ~GPIO_CRL_CNF1; // General purpose output push-pull

  // Enable the SysTick Timer with the HSI clock (8 MHz)
  SysTick->CTRL = 0x00000005; // Enable SysTick and use CPU clock
}

void loop() {
  // Turn LED ON (PA1 = 0)
  GPIOA->BSRR = GPIO_BSRR_BR1;
  delay_us(4000000); // 500 ms delay

  // Turn LED OFF (PA1 = 1)
  GPIOA->BSRR = GPIO_BSRR_BS1;
  delay_us(4000000); // 500 ms delay
}
