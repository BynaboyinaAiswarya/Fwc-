
#include<Arduino.h>
//Declaring all variables as integers
int Z=0,Y=1,X=0,W=0;
int D,C,B,A;

//Code released under GNU GPL.  Free to use for anything.
void disp_7447(int D, int C, int B, int A)
{
  digitalWrite(PB3, A); //LSB
  digitalWrite(PB4, B); 
  digitalWrite(PB5, C); 
  digitalWrite(PB6, D); //MSB

}
// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(PB3, OUTPUT);  
    pinMode(PB4, OUTPUT);
    pinMode(PB5, OUTPUT);
    pinMode(PB6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  A=(!W&&!X&&!Y&&!Z) || (!W&&X&&!Y&&!Z) || (!W&&!X&&Y&&!Z) || (!W&&X&&Y&&!Z) || (!W&&!X&&!Y&&Z);
  B=(W&&!X&&!Y&&!Z) || (!W&&X&&!Y&&!Z) || (W&&!X&&Y&&!Z) || (!W&&X&&Y&&!Z);
  C=(W&&X&&!Y&&!Z) || (!W&&!X&&Y&&!Z) || (W&&!X&&Y&&!Z) || (!W&&X&&Y&&!Z);
  D = (W&&X&&Y&&!Z) || (!W&&!X&&!Y&&Z);
  
disp_7447(D,C,B,A);  
}
//&& is the AND operation
// || is the OR operation
// ! is the NOT operation
