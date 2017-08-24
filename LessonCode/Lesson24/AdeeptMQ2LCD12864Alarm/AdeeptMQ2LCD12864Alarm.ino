/***********************************************************
File name:   AdeeptMQ2LCD12864Alarm.ino
Description: MQ2 detects smoke or gas, displayed on LCD12864,
             RGB discoloration and buzzer sound.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/03 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

int redPin = 11;         // R petal on RGB LED module connected to digital pin 11 
int greenPin = 10;       // G petal on RGB LED module connected to digital pin 10 
int bluePin = 6;         // B petal on RGB LED module connected to digital pin 6
int gassensorSPin = 7;   //connect S pin to digital 7 pin 
int gassensorAPin = 1;   //connect A pin to analog 1 pin
int passiveBuzzerPin=5;  //definition digital 5 pins as pin to control the passive buzzer

unsigned char show0[]=" MQ_2 gassensor";         //Test the code
unsigned char show1[]=" analog:       ";     
unsigned char show2[]=" www.adeept.com";  
unsigned char show3[]="  gas detected ";   
unsigned char show4[]="No gas detected";           
void setup()
{
    pinMode(redPin, OUTPUT);          //Sets the redPin to be an output 
    pinMode(greenPin, OUTPUT);        //Sets the greenPin to be an output 
    pinMode(bluePin, OUTPUT);         //Sets the bluePin to be an output 
    pinMode(gassensorAPin, INPUT);    //Set analog 0 port mode, the INPUT for the input
    pinMode(passiveBuzzerPin,OUTPUT); //Set digital 5 port mode, the OUTPUT for the output
    
    Adeept_12864.Initialise();      //The screen is initialized
    delay(100);
 // Adeept_12864.CLEAR();//Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//Display: gassensor
    delay(100);
    Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//Display: analog: 
    delay(100);
    Adeept_12864.DisplayString(3,0,show2,AR_SIZE(show3));//Display: www.adeept.com
}

void loop()
{
    double datagassensor = 0;
    char strgassensor[5];
   
    datagassensor = analogRead(gassensorAPin);
    dtostrf(datagassensor,4,0,strgassensor);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(1,4,(unsigned char *)strgassensor,4);//Display photoresistor data

    if(datagassensor>55){
       Adeept_12864.DisplayString(2,0,show3,AR_SIZE(show1));//Display: gas detected
       color(255, 0, 0);                   //Turn the RGB LED red
       tone(passiveBuzzerPin,1000);        //1000Hz frequency: 31~65535Hz 
       delay(1000);                        //set the delay time，1000ms
       noTone(passiveBuzzerPin);           //Turn off the buzzer
       delay(1000);                        //set the delay time，1000ms 
      }else{
       Adeept_12864.DisplayString(2,0,show4,AR_SIZE(show1));//Display: No gas detected
       color(0,255, 0);                    //Turn the RGB LED green  
      }
    delay(5000);

}
void color (unsigned char red, unsigned char green, unsigned char blue)// the color generating function  
{    
     analogWrite(redPin, 255-red);     // PWM signal output   
     analogWrite(greenPin, 255-green); // PWM signal output
     analogWrite(bluePin, 255-blue);   // PWM signal output
}   
