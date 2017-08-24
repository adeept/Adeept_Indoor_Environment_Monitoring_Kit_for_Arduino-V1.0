/***********************************************************
File name:  blinkingLED.ino
Description:  Lit LED, let LED blinks.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/02 
***********************************************************/
int ledPin=13; //definition digital 8 pin to control the LED on the UNO R3 board
void setup()
{
    pinMode(ledPin,OUTPUT);    //Set the digital 13 port mode, OUTPUT: Output mode
}
void loop()
{  
    digitalWrite(ledPin,HIGH); //HIGH is set to about 5V PIN13
    delay(500);                //Set the delay time, 500 = 0.5S
    digitalWrite(ledPin,LOW);  //LOW is set to about 5V PIN13
    delay(500);                //Set the delay time, 500 = 0.5S
} 
