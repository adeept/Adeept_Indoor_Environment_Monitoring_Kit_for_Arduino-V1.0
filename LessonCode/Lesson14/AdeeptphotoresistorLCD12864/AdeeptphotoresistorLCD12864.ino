/***********************************************************
File name:   AdeeptphotoresistorLCD12864.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/01 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
int photoresistorPin = 0;          // photoresistor  connected to analog pin 0
unsigned char show0[]=" photoresistor";         //Test the code
unsigned char show1[]=" analog:       ";     
unsigned char show2[]=" www.adeept.com";  
unsigned char show3[]="       Day      ";   
unsigned char show4[]="      Night     ";           
void setup()
{
    pinMode(photoresistorPin, INPUT);//Set analog 0 port mode, the INPUT for the input
    Adeept_12864.Initialise(); // The screen is initialized
    delay(100);
 // Adeept_12864.CLEAR();//Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//Display: photoresistor
    delay(100);
    Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//Display: analog: 
    delay(100);
    Adeept_12864.DisplayString(3,0,show2,AR_SIZE(show3));//Display: www.adeept.com
}

void loop()
{
    double dataphotoresistor = 0;
    char strphotoresistor[5];
   
    dataphotoresistor = analogRead(photoresistorPin);
    dtostrf(dataphotoresistor,4,0,strphotoresistor);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(1,4,(unsigned char *)strphotoresistor,4);//Display photoresistor data

    if(dataphotoresistor>500){
       Adeept_12864.DisplayString(2,0,show3,AR_SIZE(show1));//Display: Day
      }else{
        Adeept_12864.DisplayString(2,0,show4,AR_SIZE(show1));//Display: Night
        }
    delay(5000);

}
