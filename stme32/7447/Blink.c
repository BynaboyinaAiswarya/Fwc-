#include<Arduino.h>
void disp_7447(int D, int C, int B, int A)
{
  digitalWrite(PB3, A); 
  digitalWrite(PB4, B); 
  digitalWrite(PB5, C); 
  digitalWrite(PB6, D); 

}
void setup() {
    pinMode(PB3, OUTPUT);  
    pinMode(PB4, OUTPUT);
    pinMode(PB5, OUTPUT);
    pinMode(PB6, OUTPUT);
}

void loop() {
        disp_7447(0,0,0,0);
}
