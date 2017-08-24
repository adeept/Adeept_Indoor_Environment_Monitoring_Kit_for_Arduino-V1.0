/***********************************************************
File name:   SetMQ2LCD12864Alarm.ino
Description: MQ2 detects smoke or gas, displayed on LCD12864,
             RGB discoloration and buzzer sound.
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/03 
***********************************************************/
#include <Adeept_LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

int redPin = 11;         // R petal on RGB LED module connected to digital pin 11 
int greenPin = 10;       // G petal on RGB LED module connected to digital pin 10 
int bluePin = 6;         // B petal on RGB LED module connected to digital pin 6
int gassensorSPin = 7;   //connect S pin to digital 7 pin 
int gassensorAPin = 1;   //connect A pin to analog 1 pin
int passiveBuzzerPin=5;  //definition digital 5 pins as pin to control the passive buzzer
int blueButton1Pin=13;   //Set the digital 13 to blue 1 button module interface 
int blueButton2Pin=12;   //Set the digital 12 to blue 2 button module interface 
int redButtonPin=1;      //Set the digital 1 to red button module interface 
int whiteButtonPin=0;    //Set the digital 0 to white button module interface 

unsigned char show0[]=" MQ_2 gassensor";
unsigned char show1[]=" analog:       ";     
unsigned char show2[]=" www.adeept.com";  
unsigned char show3[]="  gas detected ";   
unsigned char show4[]="No gas detected"; 
unsigned char show5[]=" Set:          ";        

int page = 0; //Page control, display page and parameter settings page
double setData = 60;
void setup()
{
    pinMode(redPin, OUTPUT);          //Sets the redPin to be an output 
    pinMode(greenPin, OUTPUT);        //Sets the greenPin to be an output 
    pinMode(bluePin, OUTPUT);         //Sets the bluePin to be an output 
    pinMode(gassensorAPin, INPUT);    //Set analog 0 port mode, the INPUT for the input
    pinMode(passiveBuzzerPin,OUTPUT); //Set digital 5 port mode, the OUTPUT for the output
    
    Adeept_12864.Initialise(); // The screen is initialized
    delay(100);
 // Adeept_12864.CLEAR();//Clear screen
    delay(100);
    Adeept_12864.DisplayString(0,0,show0,AR_SIZE(show0));//Display: gassensor
    delay(100);
    Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//Display: analog: 
    delay(100);
    Adeept_12864.DisplayString(3,0,show2,AR_SIZE(show3));//Display: www.adeept.com
    pinMode(blueButton1Pin,INPUT); //Set digital 13 port mode, the INPUT for the input
    pinMode(blueButton2Pin,INPUT); //Set digital 12 port mode, the INPUT for the input
    pinMode(redButtonPin,INPUT);   //Set digital 1 port mode, the INPUT for the input
    pinMode(whiteButtonPin,INPUT); //Set digital 0 port mode, the INPUT for the input
}

void loop()
{
    double datagassensor = 0;
    char strgassensor[5];
    char strSetData[5];

    datagassensor = analogRead(gassensorAPin);
    dtostrf(datagassensor,4,0,strgassensor);//Converts a floating-point number to a string
    dtostrf(setData,4,0,strSetData);        //Converts a floating-point number to a string

    if(digitalRead(whiteButtonPin)==LOW){
       delay(10);                                  //Delay 10ms for the elimination of key leading-edge jitter
       if(digitalRead(whiteButtonPin)==LOW){       //Confirm button is pressed
           while(digitalRead(whiteButtonPin)==LOW);//Wait for key interfaces to high
           Adeept_12864.DisplayString(1,0,show1,AR_SIZE(show1));//Display: analog: 
           delay(100);
           page = 0;
        }
     }
     if(digitalRead(redButtonPin)==LOW){
       delay(10);                                //Delay 10ms for the elimination of key leading-edge jitter
       if(digitalRead(redButtonPin)==LOW){       //Confirm button is pressed  
           while(digitalRead(redButtonPin)==LOW);//Wait for key interfaces to high
           Adeept_12864.DisplayString(1,0,show5,AR_SIZE(show5));//Display: analog: 
           delay(100);
           page = 1;
        }
     }
     if(digitalRead(blueButton1Pin)==LOW){
       delay(10);                                  //Delay 10ms for the elimination of key leading-edge jitter
       if(digitalRead(blueButton1Pin)==LOW){       //Confirm button is pressed
           while(digitalRead(blueButton1Pin)==LOW);//Wait for key interfaces to high
           setData++;
           if(setData>1000){
            setData = 1000;
            }
        }
     }
     if(digitalRead(blueButton2Pin)==LOW){
       delay(10);                                  //Delay 10ms for the elimination of key leading-edge jitter
       if(digitalRead(blueButton2Pin)==LOW){       //Confirm button is pressed   
           while(digitalRead(blueButton2Pin)==LOW);//Wait for key interfaces to high
           setData--;
           if(setData<20){
            setData = 20;
            }
        }
     }
    
    if(page == 0){  //Display the detection page
      Adeept_12864.DisplayString(1,4,(unsigned char *)strgassensor,4);//Display photoresistor data
      if(datagassensor>=setData){
         Adeept_12864.DisplayString(2,0,show3,AR_SIZE(show1));//Display: gas detected
         color(255, 0, 0);                   // turn the RGB LED red
         tone(passiveBuzzerPin,1000);        //1000Hz frequency: 31~65535Hz 
         delay(1000);                        //set the delay time，1000ms
         noTone(passiveBuzzerPin);           //Turn off the buzzer
       }else{
         Adeept_12864.DisplayString(2,0,show4,AR_SIZE(show1));//Display: No gas detected
         color(0,255, 0);  //Turn the RGB LED green  
       }
    }
    if(page == 1){         //Threshold setting page
      Adeept_12864.DisplayString(1,4,(unsigned char *)strSetData,4);//Display photoresistor data
      if(datagassensor>=setData){
         Adeept_12864.DisplayString(2,0,show3,AR_SIZE(show1));//Display: gas detected
         color(255, 0, 0);                                      //Turn the RGB LED red
       }else{
         Adeept_12864.DisplayString(2,0,show4,AR_SIZE(show1));//Display: No gas detected
         color(0,255, 0);  //Turn the RGB LED green  
       }
    }
     delay(100);
}
void color (unsigned char red, unsigned char green, unsigned char blue)// the color generating function  
{    
     analogWrite(redPin, 255-red);     // PWM signal output   
     analogWrite(greenPin, 255-green); // PWM signal output
     analogWrite(bluePin, 255-blue);   // PWM signal output
}   
