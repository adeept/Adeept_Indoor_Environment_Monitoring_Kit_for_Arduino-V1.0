/***********************************************************
File name:  controlLEDByProcessing.ino
Description:  The computer controls the LED(on the UNO board)
              to light up or go off.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/04 
***********************************************************/
int ledPin=13;     //definition digital 13 pin to control the LED on the UNO R3 board.
int val;

void setup()
{
    pinMode(ledPin,OUTPUT);      //Set the digital 13 port mode, OUTPUT: Output mode
    Serial.begin(9600);         //Start the serial port, baud rate to 9600
}
void loop()
{  
   if(Serial.available()){ //Detect whether the serial data
      val = Serial.read(); //Read back the data stored in the val
    }
   if(val == 'R'){ //Analyzing the data read is not 'R'
      digitalWrite(ledPin,HIGH); // led on
    }else{
      digitalWrite(ledPin,LOW);  //led off
    }
    delay(50);
} 
