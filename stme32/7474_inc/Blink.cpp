
#include <Arduino.h>

int Z=0,Y=0,X=0,W=0;
int D,C,B,A;

void disp_7447(int D,int C,int B, int A)
{
  digitalWrite(PA0, A); //LSB
  digitalWrite(PA1, B); 
  digitalWrite(PA2, C); 
  digitalWrite(PA3, D); //MSB
}

void setup() {
 
pinMode(PA0, OUTPUT);  
pinMode(PA1, OUTPUT);
pinMode(PA2, OUTPUT);
pinMode(PA3, OUTPUT);
pinMode(PB6, INPUT);
pinMode(PB7, INPUT);
pinMode(PB8, INPUT);
pinMode(PB9, INPUT);
pinMode(PC13, OUTPUT);

}

void loop() {

digitalWrite(PC13, HIGH);
delay(100);

disp_7447(D,C,B,A);

A = (!W&&!Z)||(!W&&!X&&!Y);
B = (W&&!X&&!Z)||(!W&&X&&!Z);
C = (W&&X&&!Y&&!Z)||(!X&&Y&&!Z)||(!W&&Y&&!Z);
D = (W&&X&&Y&&!Z)||(!W&&!X&&!Y&&Z);
          
W = A;
X = B; 
Y = C;
Z = D;

digitalWrite(PC13, LOW);
delay(500);
}
