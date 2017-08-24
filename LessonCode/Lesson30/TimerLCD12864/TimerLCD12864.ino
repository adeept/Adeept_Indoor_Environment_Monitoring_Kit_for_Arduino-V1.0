/***********************************************************
File name:   TimerLCD12864.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/02 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char show0[]="  17: 15: 30";         
unsigned char show1[]="SPI interface";     
unsigned char show2[]=" www.adeept.com";  
unsigned char show3[]=" January 1,2017";     

     
unsigned long oldTime=0;
unsigned long newTime;
unsigned long time;
int Time = 17;
int Minute = 35;
int Second = 10;

void setup()
{
  Adeept_12864.Initialise(); // The screen is initialized
  delay(100);
  Adeept_12864.CLEAR();//Clear screen
  delay(100);
  Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//The first line of the third grid starts, showing
  delay(100);
  Adeept_12864.DisplayString(1,1,show1,AR_SIZE(show1));//The first line of the second line starts, display
  delay(100);
  Adeept_12864.DisplayString(2,0,show2,AR_SIZE(show2));//The third line of the first grid, display text
  delay(100);
  Adeept_12864.DisplayString(3,0,show3,AR_SIZE(show3));//The third line of the first grid, display text
  delay(100);
}

void loop()
{
  char strSecond[2];
  char strMinute[2];
  char strTime[2];
  newTime = millis();
  time = (newTime - oldTime)/1000;
  if(time>=1){
     oldTime = newTime;
     Second++;
  }
  if(Second >= 60){
     Second = 0;
     Minute++;
  }
  if(Minute>=60){
     Minute = 0;
     Time++;
   }
   if(Time>=24){
      Time = 0;
   }
  
   dtostrf(Second,2,0,strSecond);  //Converts a floating-point number to a string
   Adeept_12864.DisplayString(0,5,(unsigned char *)strSecond,2);//Display Second
   dtostrf(Minute,2,0,strMinute);  //Converts a floating-point number to a string
   Adeept_12864.DisplayString(0,3,(unsigned char *)strMinute,2);//Display Minute
   dtostrf(Time,2,0,strTime);  //Converts a floating-point number to a string
   Adeept_12864.DisplayString(0,1,(unsigned char *)strTime,2);//Display Time
   delay(100);
}
