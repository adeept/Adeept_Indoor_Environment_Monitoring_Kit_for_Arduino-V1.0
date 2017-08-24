/******************************************************************************
File name:   Processing_LED.pde
Description: Arduino and processing interactive
              
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/04 
********************************************************************************/ 
import processing.serial.*; //Transferred to the serial library
PImage img;
PImage led;
PImage redled;
Serial serial;//Create Serial objects myPoart 
PFont font;//Create font variant

void setup() { 
  // set the canvas size is 600 x 600
  size(600, 600);  
  noStroke();
  smooth();
  img = loadImage("Adeept.png");
  led = loadImage("led.png");
  redled = loadImage("redled.png");
  // Open the serial port and set the baud rate to 9600
  // This experiment arduino board is connected to COM17, here please
  // adjust according to actual situation.
  serial = new Serial(this, "COM17", 9600); 
  font = createFont("adeept",48,true);//Loading System Fonts
} 
  
void draw() { 
   // Draw a circle on canvas
    background(255); // Background to white
    image(img, 80, 90);//Display LOGO
    img.resize(450,400);
  if(mouseOverRectR() == true){ //Determine whether the mouse in a red led area
    fill(255,0,0);
    image(redled, 200, 200);//Display red led
    serial.write('R');
    delay(100);
  }else{
    image(led, 200, 200);//Display led
    fill(255,0,0);
    serial.write('G');
    delay(100);
  }
} 
boolean mouseOverRectR(){
  return ((mouseX >= 180) && (mouseX <= 380) && (mouseY >= 180) && (mouseY <= 380));
}