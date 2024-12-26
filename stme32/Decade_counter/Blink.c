#include<Arduino.h>
#define SEG_A 3
#define SEG_B 4
#define SEG_C 5
#define SEG_D 6
#define SEG_E 7
#define SEG_F 8
#define SEG_G 9

#define LED_PIN 2

volatile uint8_t count = 0;

void setup() {
  // Initialize seven-segment display pins
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);

  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);

  // Timer1 for master (1 ms interrupt)
  noInterrupts();
  TCCR1A = 0; // Clear control register A
  TCCR1B = 0; // Clear control register B
  TCNT1 = 0;  // Initialize counter
  OCR1A = 249; // Set compare match register for 1 ms (16MHz / 64 / 250 = 1kHz)
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10); // 64 prescaler
  TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt

  // Timer2 for slave (counts up to 10)
  TCCR2A = 0; // Clear control register A
  TCCR2B = 0; // Clear control register B
  TCNT2 = 0;  // Initialize counter
  OCR2A = 89; // Set compare match register for 90 Hz
  TCCR2A |= (1 << WGM21); // CTC mode
  TCCR2B |= (1 << CS22); // 64 prescaler
  TIMSK2 |= (1 << OCIE2A); // Enable timer compare interrupt

  interrupts(); // Enable global interrupts
}

void loop() {
  // Display the current count on the seven-segment display
  displayNumber(count);
}

// Timer1 interrupt service routine (1 ms)
ISR(TIMER1_COMPA_vect) {
  static uint16_t masterCounter = 0;

  masterCounter++;
  if (masterCounter >= 1000) { // 1-second interval
    masterCounter = 0;
    TCNT2++; // Increment slave timer manually
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
  }
}

// Timer2 interrupt service routine (counts to 10)
ISR(TIMER2_COMPA_vect) {
  if (++count >= 10) {
    count = 0; // Reset count
  }
}

// Function to display a number on the seven-segment display
void displayNumber(uint8_t num) {
  digitalWrite(SEG_A, num != 1 && num != 4);
  digitalWrite(SEG_B, num != 5 && num != 6);
  digitalWrite(SEG_C, num != 2);
  digitalWrite(SEG_D, num != 1 && num != 4 && num != 7);
  digitalWrite(SEG_E, num == 2 || num == 6 || num == 8 || num == 0);
  digitalWrite(SEG_F, num != 1 && num != 2 && num != 3 && num != 7);
  digitalWrite(SEG_G, num != 0 && num != 1 && num != 7);
}

