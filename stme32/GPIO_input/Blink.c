#include<Arduino.h>
// Define pin connections
const int ledPin = 4;  // LED connected to PB4
const int buttonPin = 7;  // Button connected to PB7

void setup() {
  // Configure LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Configure button pin as input
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
}

void loop() {
  // Check the state of the button
  if (digitalRead(buttonPin) == LOW) {  // Button pressed
    digitalWrite(ledPin, LOW);  // Turn LED ON
  } else {  // Button not pressed
    digitalWrite(ledPin, HIGH);  // Turn LED OFF
  }
}
