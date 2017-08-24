/***********************************************************
File name:   AdeeptDHT11LCD12864Alarm.ino
Description:DHT11 detects temperature and humidity display on
            LCD12864, exceeds the set threshold, RGB discoloration
            and buzzer sound.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/03 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#include <Adeept_DHT11.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
Adeept_DHT11 Adeept_dht11;
#define DHT11PIN 2        //Set the digital 2 to the S pin

int redPin = 11;          // R petal on RGB LED module connected to digital pin 11 
int greenPin = 10;        // G petal on RGB LED module connected to digital pin 10 
int bluePin = 6;          // B petal on RGB LED module connected to digital pin 6
int passiveBuzzerPin = 5; //definition digital 5 pins as pin to control the passive buzzer

unsigned char show0[]="DHT11 sensor";         
unsigned char show1[]="Humi:       %";     
unsigned char show2[]="Temp:       C";   
unsigned char show3[]=" www.adeept.com";          

void setup()
{
    Adeept_dht11.read(DHT11PIN);
    Adeept_12864.Initialise(); // The screen is initialized
    delay(100);
    Adeept_12864.CLEAR();      //Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,1,show0,AR_SIZE(show0));//Display: DHT11 sensor
    delay(100);
    Adeept_12864.DisplayString(1,1,show1,AR_SIZE(show1));//Display: Humi:     %
    delay(100);
    Adeept_12864.DisplayString(2,1,show2,AR_SIZE(show2));//Display: Temp:     C
    delay(100);
    Adeept_12864.DisplayString(3,0,show3,AR_SIZE(show3));//Display: www.adeept.com
    pinMode(redPin, OUTPUT);          // sets the redPin to be an output 
    pinMode(greenPin, OUTPUT);        // sets the greenPin to be an output 
    pinMode(bluePin, OUTPUT);         // sets the bluePin to be an output 
    pinMode(passiveBuzzerPin,OUTPUT); // set digital 5 port mode, the OUTPUT for the output
}

void loop()
{
    double temphumidity = 0;
    double tempTemperature = 0;
    char strhumidity[5];
    char strTemperature[5];
   
    temphumidity = Adeept_dht11.humidity;
    dtostrf(temphumidity,5,2,strhumidity);                           //Converts a floating-point number to a string
    Adeept_12864.DisplayString(1,4,(unsigned char *)strhumidity,6);//Display humidity data

    tempTemperature = Adeept_dht11.temperature;
    dtostrf(tempTemperature,5,2,strTemperature);                        //Converts a floating-point number to a string
    Adeept_12864.DisplayString(2,4,(unsigned char *)strTemperature,6);//Display temperature data
    if(temphumidity>44||tempTemperature>27){
      color(255, 0, 0);                   //Turn the RGB LED red  
      tone(passiveBuzzerPin,1000);        //1000Hz frequency: 31~65535Hz 
      delay(1000);                        //Set the delay time，1000ms
      noTone(passiveBuzzerPin);           //Turn off the buzzer
      delay(1000);                        //Set the delay time，1000ms 
    }else{
      color(0,255, 0);                    //Turn the RGB LED green 
    }
    delay(1000);
}
void color (unsigned char red, unsigned char green, unsigned char blue)// the color generating function  
{    
     analogWrite(redPin, 255-red);     // PWM signal output   
     analogWrite(greenPin, 255-green); // PWM signal output
     analogWrite(bluePin, 255-blue);   // PWM signal output
} 
