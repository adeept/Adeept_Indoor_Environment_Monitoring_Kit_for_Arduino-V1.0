/***********************************************************
File name: RGB_LED_Button.ino
Description:Press the button on the LCD12864 to press
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/03
*************************************************************/
#include <Adeept_LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
int blueButton1Pin=13;   //Set the digital 13 to blue 1 button module interface 
int blueButton2Pin=12;   //Set the digital 12 to blue 2 button module interface 
int redButtonPin=1;      //Set the digital 1 to red button module interface 
int whiteButtonPin=0;    //Set the digital 0 to white button module interface 
unsigned char show0[]="Button 1       ";         
unsigned char show1[]="Button 2       ";     
unsigned char show2[]="Button 3       ";  
unsigned char show3[]="Button 4       "; 
unsigned char show4[]="Press";    

void setup()    
{   
   Adeept_12864.Initialise(); // The screen is initialized
   delay(100);
   Adeept_12864.CLEAR();//Clear screen
   delay(100);
   Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//The first line of the third grid starts, showing
   delay(100);
   Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//The first line of the second line starts, display
   delay(100);
   Adeept_12864.DisplayString(2,0,show2,AR_SIZE(show2));//The third line of the first grid, display text
   delay(100);
   Adeept_12864.DisplayString(3,0,show3,AR_SIZE(show3));//The third line of the first grid, display text
   delay(100);
   pinMode(blueButton1Pin,INPUT); //Set digital 13 port mode, the INPUT for the input
   pinMode(blueButton2Pin,INPUT); //Set digital 12 port mode, the INPUT for the input
   pinMode(redButtonPin,INPUT);   //Set digital 1 port mode, the INPUT for the input
   pinMode(whiteButtonPin,INPUT); //Set digital 0 port mode, the INPUT for the input

}    
void loop()  // run over and over again  
{    
  if(digitalRead(blueButton1Pin)==LOW) //Detection button interface to low
  {   
      delay(10); //Delay 10ms for the elimination of key leading-edge jitter
      if(digitalRead(blueButton1Pin)==LOW) //Confirm button is pressed
      {    
         Adeept_12864.DisplayString(0,5,show4,AR_SIZE(show4));
         delay(100);        // delay for 0.1 second   
      }
   }else{
         Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//The first line of the third grid starts, showing
         delay(100);        // delay for 0.1 second  
      }
  if(digitalRead(blueButton2Pin)==LOW) //Detection button interface to low
  {   
      delay(10);  //Delay 10ms for the elimination of key leading-edge jitter
      if(digitalRead(blueButton2Pin)==LOW) //Confirm button is pressed
      {     
         Adeept_12864.DisplayString(1,5,show4,AR_SIZE(show4));
         delay(100);       // delay for 0.1 second  
       }
   }else{
         Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//The first line of the second line starts, display
         delay(100);
      }
  if(digitalRead(redButtonPin)==LOW) //Detection button interface to low
  {   
      delay(10);  //Delay 10ms for the elimination of key leading-edge jitter
      if(digitalRead(redButtonPin)==LOW) //Confirm button is pressed
      {       
         Adeept_12864.DisplayString(2,5,show4,AR_SIZE(show4));
         delay(100);       // delay for 0.1 second  
       }
   }else{
         Adeept_12864.DisplayString(2,0,show2,AR_SIZE(show2));//The third line of the first grid, display text
         delay(100);
      }   
  if(digitalRead(whiteButtonPin)==LOW) //Detection button interface to low
  {   
      delay(10);  //Delay 10ms for the elimination of key leading-edge jitter
      if(digitalRead(whiteButtonPin)==LOW) //Confirm button is pressed
      {       
         Adeept_12864.DisplayString(3,5,show4,AR_SIZE(show4));
         delay(100);       // delay for 0.1 second  
       }
   }else{
         Adeept_12864.DisplayString(3,0,show3,AR_SIZE(show3));//The third line of the first grid, display text
         delay(100);
      } 
   delay(100);       // delay for 0.1 second 
}     
