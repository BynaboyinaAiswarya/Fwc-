#include "stm32f103xb.h"

void sysinit(void);
void master(uint16_t psc, uint16_t arr, uint8_t rcr);
void slave(uint16_t psc, uint16_t arr);
void sevenseg(uint8_t dec);

void setup()
{
    sysinit();
    // Initialize Timer1 as master with desired parameters
    master(1, 249, 1); // 8MHz / (2 x 250 x 2) = 8kHz
    // Initialize Timer2 as slave with desired parameters
    slave(8999, 9);    // 8kHz / (9000) = ~0.89Hz
}

void loop()
{
    // Display the value from Timer2's CNT register on the 7-segment display
    sevenseg(TIM2->CNT);

    // Blink LED on PA1 for half-second intervals
    if (TIM2->SR & 0x0001) // Check if TIM2 ARR count is complete
    {
        TIM2->SR &= ~0x0001; // Clear the TIM2 status register SR
        GPIOA->ODR ^= (1 << 1); // Toggle the LED connected to PA1
    }
}

void sysinit(void)
{
    /*
     * Enable all Ports and Alternate Function clocks
     */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
        RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;

    /* Enable the timer peripherals */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // Enable Timer1
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Enable Timer2

    /*
     * Disable JTAG and SWO (Free PB3, PB4 and PA15)
     */
    AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    /*
     * Enable PA1 as a digital output
     */
    GPIOA->CRL = 0x00000030;

    /*
     * Enable PB3-PB9 as digital outputs
     */
    GPIOB->CRL = 0x33333000;
    GPIOB->CRH = 0x00000033;
}

void master(uint16_t psc, uint16_t arr, uint8_t rcr)
{
    TIM1->SMCR = 0;        // Internal clock, 8MHz
    TIM1->PSC = psc;       // Prescalar
    TIM1->ARR = arr;       // Auto-reload register
    TIM1->RCR = rcr;       // Repetition count
    TIM1->CR2 = 0x0020;    // MMS = 010
    TIM1->CR1 = 0x0001;    // Enable Timer1
}

void slave(uint16_t psc, uint16_t arr)
{
    TIM2->PSC = psc;       // Prescalar
    TIM2->SMCR = 0x0007;   // TS = 000, SMS = 111
    TIM2->ARR = arr;       // Auto-reload register
    TIM2->CR1 = 0x0001;    // Enable Timer2
}

void sevenseg(uint8_t dec)
{
    switch (dec)
    {
    case 0:
        GPIOB->BRR = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
        GPIOB->BSRR = (1 << 3);
        break;

    case 1:
        GPIOB->BRR = (1 << 7) | (1 << 8);
        GPIOB->BSRR = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 9);
        break;

    case 2:
        GPIOB->BRR = (1 << 3) | (1 << 5) | (1 << 6) | (1 << 8) | (1 << 9);
        GPIOB->BSRR = (1 << 4) | (1 << 7);
        break;

    case 3:
        GPIOB->BRR = (1 << 3) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
        GPIOB->BSRR = (1 << 4) | (1 << 5);
        break;

    case 4:
        GPIOB->BRR = (1 << 3) | (1 << 4) | (1 << 7) | (1 << 8);
        GPIOB->BSRR = (1 << 5) | (1 << 6) | (1 << 9);
        break;

    case 5:
        GPIOB->BRR = (1 << 3) | (1 << 4) | (1 << 6) | (1 << 7) | (1 << 9);
        GPIOB->BSRR = (1 << 5) | (1 << 8);
        break;

    case 6:
        GPIOB->BRR = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 9);
        GPIOB->BSRR = (1 << 8);
        break;

    case 7:
        GPIOB->BRR = (1 << 7) | (1 << 8) | (1 << 9);
        GPIOB->BSRR = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6);
        break;

    case 8:
        GPIOB->BRR = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
        break;

    case 9:
        GPIOB->BRR = (1 << 3) | (1 << 4) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);
        GPIOB->BSRR = (1 << 5);
        break;

    default:
        GPIOB->BRR = (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 9);
        GPIOB->BSRR = (1 << 7) | (1 << 8);
        break;
    }
}

