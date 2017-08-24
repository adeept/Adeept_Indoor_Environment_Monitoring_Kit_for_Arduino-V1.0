/***********************************************************
File name: Buzzer.ino
Description: The passive buzzer beeps like the sound of "Di Di"..
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/02 
***********************************************************/
int passiveBuzzerPin=5; //definition digital 5 pins as pin to control the passive buzzer
void setup()
{
    pinMode(passiveBuzzerPin,OUTPUT); //set digital 8 port mode, the OUTPUT for the output
}
void loop()
{  
    tone(passiveBuzzerPin,31);          //31Hz frequency: 31~65535Hz 
    delay(1000);                        //set the delay time，1000ms
    noTone(passiveBuzzerPin);           //Turn off the buzzer
    delay(2000);                        //set the delay time，2000ms 
    
    tone(passiveBuzzerPin,100);         //100Hz frequency: 31~65535Hz 
    delay(1000);                        //set the delay time，1000ms
    noTone(passiveBuzzerPin);           //Turn off the buzzer
    delay(2000);                        //set the delay time，2000ms 
    
    tone(passiveBuzzerPin,1000);        //1000Hz frequency: 31~65535Hz      
    delay(1000);                        //set the delay time，1000ms
    noTone(passiveBuzzerPin);           //Turn off the buzzer
    delay(2000);                        //set the delay time，2000ms 
}
