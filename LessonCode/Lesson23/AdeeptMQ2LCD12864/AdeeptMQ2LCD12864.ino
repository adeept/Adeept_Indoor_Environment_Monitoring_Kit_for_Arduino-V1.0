/***********************************************************
File name:   AdeeptMQ2LCD12864.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/01 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
int gassensorSPin = 7;//connect S pin to digital 7 pin 
int gassensorAPin = 1;//connect A pin to analog 1 pin
unsigned char show0[]=" MQ_2 gassensor";         //Test the code
unsigned char show1[]=" analog:       ";     
unsigned char show2[]=" www.adeept.com";  
unsigned char show3[]="  gas detected ";   
unsigned char show4[]="No gas detected";           
void setup()
{
    pinMode(gassensorAPin, INPUT);//Set analog 0 port mode, the INPUT for the input
    Adeept_12864.Initialise(); // The screen is initialized
    delay(100);
 // Adeept_12864.CLEAR();//Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//Display: gassensor
    delay(100);
    Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//Display: analog: 
    delay(100);
    Adeept_12864.DisplayString(3,0,show2,AR_SIZE(show3));//Display: www.adeept.com
    Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
}

void loop()
{
    double datagassensor = 0;
    char strgassensor[5];
   
    datagassensor = analogRead(gassensorAPin);
    Serial.println(analogRead(1));         //send analog data(A pin) to the serial monitor
    dtostrf(datagassensor,4,0,strgassensor);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(1,4,(unsigned char *)strgassensor,4);//Display photoresistor data

    if(datagassensor>52){
       Adeept_12864.DisplayString(2,0,show3,AR_SIZE(show1));//Display: gas detected
      }else{
        Adeept_12864.DisplayString(2,0,show4,AR_SIZE(show1));//Display: No gas detected
        }
    delay(5000);

}
