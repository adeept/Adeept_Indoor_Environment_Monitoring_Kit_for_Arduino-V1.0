/**********************************************************************
File name: barometerDisplaySerial.ino
Description:   Get pressure, altitude, and temperature from the BMP180.
               Serial.print it out at 9600 baud to serial monitor.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/02
************************************************************************/

#include <Adeept_BMP180.h>

Adeept_BMP180 Adeept_bmp180(0x77);//I2C address of BMP180

void setup() {
  Serial.begin(9600);
  Adeept_bmp180.begin();

}

void loop()
{
  float temperature = Adeept_bmp180.GetTemperature(); 
  float pressure = Adeept_bmp180.GetPressure();
  float atm = pressure / 101325; // "standard atmosphere"
  float altitude = Adeept_bmp180.calcAltitude(pressure); //Uncompensated caculation - in Meters

  Serial.print("Temperature: ");
  Serial.print(temperature, 2); //display 2 decimal places
  Serial.println("deg C");

  Serial.print("Pressure: ");
  Serial.print(pressure, 0);    //whole number only.
  Serial.println(" Pa");

  Serial.print("Standard Atmosphere: ");
  Serial.println(atm, 4);       //display 4 decimal places

  Serial.print("Altitude: ");
  Serial.print(altitude, 2);    //display 2 decimal places
  Serial.println(" M");

  Serial.println();//line break

  delay(1000); //wait a second and get values again.
}


