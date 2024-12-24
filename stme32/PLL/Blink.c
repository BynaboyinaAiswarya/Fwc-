#include<Arduino.h>
// Define LED pin
const int ledPin = 1; // PA1 corresponds to pin 1 in Arduino

// Custom delay function for microseconds
void delayMicrosecondsCustom(uint32_t time) {
  uint32_t startTime = micros();
  while ((micros() - startTime) < time) {
    // Wait for the specified duration
  }
}

void setup() {
  // Configure LED pin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Blink LED with 24 MHz clock timing emulation
  // Turn LED OFF
  digitalWrite(ledPin, HIGH); // Assuming active-low LED
  delayMicrosecondsCustom(500000); // Adjusted for 500ms delay at 24 MHz

  // Turn LED ON
  digitalWrite(ledPin, LOW); // Assuming active-low LED
  delayMicrosecondsCustom(500000); // Adjusted for 500ms delay at 24 MHz
}

