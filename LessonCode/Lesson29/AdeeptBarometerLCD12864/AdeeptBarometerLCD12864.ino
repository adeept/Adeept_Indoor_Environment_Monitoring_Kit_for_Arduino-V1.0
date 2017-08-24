/**********************************************************************
  File name: AdeeptBarometerLCD12864.ino
  Description:   Get pressure, altitude, and temperature from the BMP180
               Serial.print it out at 9600 baud to serial monitor.
  Website: www.adeept.com
  E-mail: support@adeept.com
  Author: Tom
  Date: 2017/03/05
************************************************************************/
#include <Adeept_LCD12864RSPI.h>
#include <Adeept_BMP180.h>

#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )


Adeept_BMP180 Adeept_bmp180(0x77);//I2C address of BMP180

unsigned char show0[] = "Temp:        C  ";      
unsigned char show1[] = "Pres:        Pa ";
unsigned char show2[] = "Atm:            ";
unsigned char show3[] = "Alti:        M  ";

void setup() {
  Adeept_bmp180.begin();
  Adeept_12864.Initialise(); // The screen is initialized
  delay(100);
  // Adeept_lcd12864.CLEAR();//Clear screen
  delay(100);
  Adeept_12864.DisplayString(0, 0, show0, AR_SIZE(show0)); //Display: Temp:      C
  delay(100);
  Adeept_12864.DisplayString(1, 0, show1, AR_SIZE(show1)); //Display: Pres:        Pa
  delay(100);
  Adeept_12864.DisplayString(2, 0, show2, AR_SIZE(show2)); //Display: Atm:         Pa
  delay(100);
  Adeept_12864.DisplayString(3, 0, show3, AR_SIZE(show3)); //Display: Altitude:     M
}

void loop()
{
  char strTemperature[5];
  char strPressure[5];
  char strAtm[5];
  char strAltitude[5];

  float dataTemperature = Adeept_bmp180.GetTemperature(); //MUST be called first
  float dataPressure = Adeept_bmp180.GetPressure();
  float dataAtm = dataPressure / 101325; // "standard atmosphere"
  float dataAltitude = Adeept_bmp180.calcAltitude(dataPressure); //Uncompensated caculation - in Meters

  dtostrf(dataTemperature, 5, 2, strTemperature); //Converts a floating-point number to a string
  Adeept_12864.DisplayString(0, 3, (unsigned char *)strTemperature, 6); //Display humidity data

  dtostrf(dataPressure, 5, 2, strPressure); //Converts a floating-point number to a string
  Adeept_12864.DisplayString(1, 3, (unsigned char *)strPressure, 6); //Display temperature data

  dtostrf(dataAtm, 5, 4, strAtm); //Converts a floating-point number to a string
  Adeept_12864.DisplayString(2, 3, (unsigned char *)strAtm, 6); //Display temperature data

  dtostrf(dataAltitude, 5, 2, strAltitude); //Converts a floating-point number to a string
  Adeept_12864.DisplayString(3, 3, (unsigned char *)strAltitude, 6); //Display temperature data
  
  delay(5000);
}


