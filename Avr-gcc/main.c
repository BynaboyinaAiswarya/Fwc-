#include <avr/io.h>    // AVR register definitions

#define D2_PIN PD2     // D2 connected to digital pin 2 (Port D, pin 2)
#define D3_PIN PD3     // D3 connected to digital pin 3 (Port D, pin 3)
#define B_PIN  PB5     // B connected to digital pin 13 (Port B, pin 5)

void setup_pins(void) {
    // Set D2_PIN, D3_PIN as inputs (0 in DDRx register)
    DDRD &= ~(1 << D2_PIN);   // Clear bit for D2
    DDRD &= ~(1 << D3_PIN);   // Clear bit for D3

    // Set B_PIN as output (1 in DDRx register)
    DDRB |= (1 << B_PIN);     // Set bit for B (pin 13)
}

int main(void) {
    // Setup the input/output pins
    setup_pins();

    while (1) {
        // Read input values from the D pins
        int D2 = (PIND & (1 << D2_PIN)) >> D2_PIN;
        int D3 = (PIND & (1 << D3_PIN)) >> D3_PIN;

        // Logic for B = D3 XOR D2
        int B = D3 ^ D2;

        // Set or clear the B_PIN based on the value of B
        if (B) {
            PORTB |= (1 << B_PIN);  // Set B_PIN to high (output 1)
        } else {
            PORTB &= ~(1 << B_PIN); // Clear B_PIN to low (output 0)
        }
    }

    return 0;
}
