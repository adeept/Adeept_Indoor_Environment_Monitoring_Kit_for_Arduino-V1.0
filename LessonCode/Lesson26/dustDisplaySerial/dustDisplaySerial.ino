/***********************************************************
File name: dustDisplaySerial.ino
Description:  Use the GP2 sensor to detect the environment
             you will see the data in the serial monitor 
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/02 
***********************************************************/
#include <Adeept_GP2.h>

int PIN_DATA_OUT = 2; //Connect the IO port of the GP2 sensor analog A2 output
int  PIN_LED_VCC = 4; //The pin in the GP2 sensor that supplies power to the internal Led
Adeept_GP2  Adeept_gp2(PIN_DATA_OUT, PIN_LED_VCC);
void setup() {
  Serial.begin(115200);
  Adeept_gp2.begin();
}

void loop() {
  double outputV = Adeept_gp2.getOutputV(); //Sampling Get the output voltage
  double ugm3 = Adeept_gp2.getDustDensity(outputV); //Calculate the dust concentration
  double aqi = Adeept_gp2.getAQI(ugm3); //Calculate aqi
  String gradeInfo = Adeept_gp2.getGradeInfo(aqi); //Calculate the level

  //Print to the serial port
  Serial.println(String("outputV=") + outputV + "\tug/m3=" + ugm3 + "\tAQI=" + aqi + "\tgradeInfo=" + gradeInfo);

  //The next detection is performed every 1 second
  delay(1000);
}
