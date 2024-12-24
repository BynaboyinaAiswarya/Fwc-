#include<Arduino.h>
// Define LED pin
const int ledPin = 1; // LED connected to PA1

void delayMicrosecondsCustom(uint32_t time) {
  // Custom delay using micros() function
  uint32_t start = micros();
  while ((micros() - start) < time) {
    // Wait until the specified time has passed
  }
}

void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn LED OFF
  digitalWrite(ledPin, HIGH); 
  delayMicrosecondsCustom(4000000); // 500ms delay

  // Turn LED ON
  digitalWrite(ledPin, LOW); 
  delayMicrosecondsCustom(4000000); // 500ms delay
}
