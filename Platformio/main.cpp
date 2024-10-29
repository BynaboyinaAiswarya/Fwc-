#include <Arduino.h>
const int inputU = 2;
const int inputV = 3;
const int inputW = 4;
const int inputX = 5;
const int outputPin = 13;

void setup() {
  pinMode(inputU, INPUT);
  pinMode(inputV, INPUT);
  pinMode(inputW, INPUT);
  pinMode(inputX, INPUT);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  // Read input values
  bool u = digitalRead(inputU);
  bool v = digitalRead(inputV);
  bool w = digitalRead(inputW);
  bool x = digitalRead(inputX);

  // Output logic based on the expression
  bool output = (!w && (u && !v) || (!u && v));

  // Write to the output pin
  digitalWrite(outputPin, output);
}
