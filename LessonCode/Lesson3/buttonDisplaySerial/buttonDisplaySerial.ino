/***********************************************************
File name: buttonDisplaySerial.ino
Description: When you press the button, you can see the state
             of the serial monitor.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/03 
***********************************************************/

int btnpin=12;           //Set the digital 12 to button module interface 

void setup()
{
  Serial.begin(9600);   //opens serial port, sets data rate to 9600 bps
  pinMode(btnpin,INPUT); //Set digital 12 port mode, the INPUT for the input
}

void loop()
{
  if(digitalRead(btnpin)==HIGH)              //Detection button interface to low
  {   
      delay(10);                              //Delay 10ms for the elimination of key leading-edge jitter
      if(digitalRead(btnpin)==HIGH)           //Confirm button is pressed
      {     
        while(digitalRead(btnpin)==HIGH);     //Wait for key interfaces to high
        delay(10);                            //delay 10ms for the elimination of key trailing-edge jitter
        while(digitalRead(btnpin)==HIGH);     //Confirm button release
         Serial.println("Press the button"); //send data to the serial monitor
      }
   }
   delay(100); //delay 0.1 s
}
