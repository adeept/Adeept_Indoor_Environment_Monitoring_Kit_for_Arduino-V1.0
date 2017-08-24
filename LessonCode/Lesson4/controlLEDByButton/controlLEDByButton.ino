/***********************************************************
File name: controlLEDByButton.ino
Description: When you press the button, you can see the state
             of the LED will be toggled. (ON->OFF，OFF->ON).
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/03 
***********************************************************/

int ledpin=13;            //definition digital 13 pins as pin to control the LED module
int btnpin=12;            //Set the digital 12 to button module interface 

volatile int state = LOW; // Defined output status LED Interface

void setup()
{
  pinMode(ledpin,OUTPUT);//Set digital 13 port mode, the OUTPUT for the output
  pinMode(btnpin,INPUT); //Set digital 12 port mode, the INPUT for the input
}

void loop()
{
  if(digitalRead(btnpin)==HIGH)          //Detection button interface to low
  {   
      delay(10);                        //Delay 10ms for the elimination of key leading-edge jitter
      if(digitalRead(btnpin)==HIGH)      //Confirm button is pressed
      {     
        while(digitalRead(btnpin)==HIGH);//Wait for key interfaces to high
        delay(10);                      //delay 10ms for the elimination of key trailing-edge jitter
        while(digitalRead(btnpin)==HIGH);//Confirm button release
        state = !state;                 //Negate operation, each time you run the program here, state the HGIH becomes LOW, or the state becomes the LOW HGIH.
        digitalWrite(ledpin,state);     //Output control status LED, ON or OFF 
      }
   }
}
