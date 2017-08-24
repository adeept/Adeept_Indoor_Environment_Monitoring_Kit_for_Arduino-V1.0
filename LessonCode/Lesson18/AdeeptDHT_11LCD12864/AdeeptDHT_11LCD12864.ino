/***********************************************************
File name:   AdeeptDHT_11LCD12864.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/01/04 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#include <Adeept_DHT11.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
Adeept_DHT11 Adeept_dht11;
#define DHT11PIN 2  //Set the digital 2 to the S pin

unsigned char show0[]="DHT11 sensor";      
unsigned char show1[]="Humi:       %";     
unsigned char show2[]="Temp:       C";   
unsigned char show3[]=" www.adeept.com";          


void setup()
{
    Adeept_dht11.read(DHT11PIN);
    Adeept_12864.Initialise(); // The screen is initialized
    delay(100);
 // Adeept_12864.CLEAR();//Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,1,show0,AR_SIZE(show0));//Display: DHT11 sensor
    delay(100);
    Adeept_12864.DisplayString(1,1,show1,AR_SIZE(show1));//Display: Humi:     %
    delay(100);
    Adeept_12864.DisplayString(2,1,show2,AR_SIZE(show2));//Display: Temp:     C
    delay(100);
    Adeept_12864.DisplayString(3,0,show3,AR_SIZE(show3));//Display: www.adeept.com
}

void loop()
{
    double temphumidity = 0;
    double tempTemperature = 0;
    char strhumidity[5];
    char strTemperature[5];
   
    temphumidity = Adeept_dht11.humidity;
    dtostrf(temphumidity,5,2,strhumidity);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(1,4,(unsigned char *)strhumidity,6);//Display humidity data

    tempTemperature = Adeept_dht11.temperature;
    dtostrf(tempTemperature,5,2,strTemperature);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(2,4,(unsigned char *)strTemperature,6);//Display temperature data
    delay(5000);

}
