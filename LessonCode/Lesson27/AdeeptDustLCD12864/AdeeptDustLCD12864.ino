/***********************************************************
File name:   AdeeptDustLCD12864.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/02 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#include <Adeept_GP2.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
int PIN_DATA_OUT = 2; //Connect the IO port of the GP2 sensor analog A2 output
int PIN_LED_VCC = 4;  //The pin in the GP2 sensor that supplies power to the internal Led
Adeept_GP2  Adeept_gp2(PIN_DATA_OUT, PIN_LED_VCC);

unsigned char show0[] = "GP2 Valt:     V";         
unsigned char show1[] = "ugm3:          ";     
unsigned char show2[] = "aqi:           ";   
unsigned char show3[] = "             ";  
unsigned char show4[] = "     Perfect    ";
unsigned char show5[] = "      Good      ";
unsigned char show6[] = "Mild polluted   ";
unsigned char show7[] = "Medium polluted ";
unsigned char show8[] = "Heavily polluted";
unsigned char show9[] = "Severe polluted ";
unsigned char show10[] = " Broken roof!!! ";
          
void setup()
{
    Adeept_12864.Initialise(); // The screen is initialized
    delay(100);
 // Adeept_12864.CLEAR();//Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//Display: 
    delay(100);
    Adeept_12864.DisplayString(1,1,show1,AR_SIZE(show1));//Display: 
    delay(100);
    Adeept_12864.DisplayString(2,1,show2,AR_SIZE(show2));//Display:
    delay(100);
    Adeept_12864.DisplayString(3,0,show3,AR_SIZE(show3));//Display:
    Adeept_gp2.begin();
}

void loop()
{
    double tempOutputV = 0;
    double tempUgm3 = 0;
    double tempAqi = 0;   
    char strOutputV[5];
    char strUgm3[5];
    char strAqi[5];
    
    tempOutputV = Adeept_gp2.getOutputV(); //Sampling Get the output voltage
    dtostrf(tempOutputV,5,2,strOutputV);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(0,4,(unsigned char *)strOutputV,6);//Display humidity data

    tempUgm3 = Adeept_gp2.getDustDensity(tempOutputV); //Calculate the dust concentration
    dtostrf(tempUgm3,5,2,strUgm3);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(1,4,(unsigned char *)strUgm3,6);//Display temperature data

    tempAqi = Adeept_gp2.getAQI(tempUgm3); //Calculate aqi
    dtostrf(tempAqi,5,2,strAqi);//Converts a floating-point number to a string
    Adeept_12864.DisplayString(2,4,(unsigned char *)strAqi,6);//Display temperature data

    if (tempAqi >= 0 && tempAqi <= 50) {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show4,16);//Display 
    } else if (tempAqi > 50 && tempAqi <= 100) {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show5,16);//Display 
    } else if (tempAqi > 100 && tempAqi <= 150) {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show6,16);//Display 
    } else if (tempAqi > 150 && tempAqi <= 200) {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show7,16);//Display 
    } else if (tempAqi > 200 && tempAqi <= 300) {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show8,16);//Display 
    } else if (tempAqi > 300 && tempAqi <= 500) {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show9,16);//Display 
    } else {
      Adeept_12864.DisplayString(3,0,(unsigned char *)show10,16);//Display 
    }
    delay(1000);

}
