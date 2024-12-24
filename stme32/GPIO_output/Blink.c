// Blink LED on PA1 using Arduino IDE with STM32 core
#include<Arduino.h>
void delay_us(uint32_t time) {
  // Arduino delayMicroseconds function handles this natively
  delayMicroseconds(time);
}

void setup() {
  // Initialize PA1 as output
  pinMode(PA1, OUTPUT);
}

void loop() {
  digitalWrite(PA1, HIGH); // Turn LED off (assuming active LOW)
  delay(500);              // 500ms delay
  digitalWrite(PA1, LOW);  // Turn LED on
  delay(500);              // 500ms delay
}

