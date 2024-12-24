
#include <Arduino.h>

// Pin assignments for the 7447 decoder inputs
#define A_PIN PB3 // LSB
#define B_PIN PB4
#define C_PIN PB5
#define D_PIN PB6 // MSB

int count = 9; // Start from 9 for decrementing

// Function to display a 4-bit binary number on the 7447 decoder
void disp_7447(int D, int C, int B, int A) {
  digitalWrite(A_PIN, A); // LSB
  digitalWrite(B_PIN, B);
  digitalWrite(C_PIN, C);
  digitalWrite(D_PIN, D); // MSB
}

// Function to extract and display binary representation
void updateDisplay(int number) {
  int A = number & 0x01;      // Extract the least significant bit
  int B = (number >> 1) & 0x01;
  int C = (number >> 2) & 0x01;
  int D = (number >> 3) & 0x01;
  
  disp_7447(D, C, B, A); // Send to display
}

void setup() {
  // Set all decoder pins as outputs
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);

  // Initialize display with starting value
  updateDisplay(count);
}

void loop() {
  delay(1000); // Delay for 1 second

  // Update the display
  updateDisplay(count);

  // Decrement the count
  count--;

  // If count goes below 0, reset to 9
  if (count < 0) {
    count = 9;
  }
}
