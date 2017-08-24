/***********************************************************
File name:  buttonDisplayViaProcessing.ino
Description: Detects four key messages and sends key information 
             to the serial port
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/04 
***********************************************************/
int redbuttonPin=2;      //definition digital 2 pin to control the button module
int whitebuttonPin=3;    //definition digital 3 pin to control the button module
int bluebutton1Pin=13;   //definition digital 13 pin to control the button module
int bluebutton2Pin=12;   //definition digital 12 pin to control the button module
int val;

void setup()
{
    pinMode(redbuttonPin,INPUT);       //Set the digital 2 port mode,  INPUT mode
    pinMode(whitebuttonPin,INPUT);     //Set the digital 3 port mode,  INPUT mode
    pinMode(bluebutton1Pin,INPUT);     //Set the digital 13 port mode, INPUT mode
    pinMode(bluebutton2Pin,INPUT);     //Set the digital 12 port mode, INPUT mode   
    Serial.begin(9600);               // Start the serial port, baud rate to 9600
}
void loop()
{  
    if(digitalRead(redbuttonPin)==LOW){  //Detection button interface to low
         val = val|0x01;    
    }else{
         val = val&0x0E; 
    }
     if(digitalRead(whitebuttonPin)==LOW){  //Detection button interface to low
          val = val|0x02;     
     }else{
          val = val&0x0D; 
     }
     if(digitalRead(bluebutton1Pin)==LOW){  //Detection button interface to low
          val = val|0x04;   
      }else{
          val = val&0x0B;  
     }
     if(digitalRead(bluebutton2Pin)==LOW){  //Detection button interface to low
         val = val|0x08;   
       }else{
         val = val&0x07; 
    }
    Serial.write(val); //send data to the serial monitor  
    delay(50);
} 
