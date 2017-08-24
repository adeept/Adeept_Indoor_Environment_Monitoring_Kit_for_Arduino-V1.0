/******************************************************************************
File name:   Processing_RGB.pde
Description: Arduino and processing interactive
             Processing receives information from Arduino and displays the 
             information
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/03/04 
********************************************************************************/ 
import processing.serial.*; //Transferred to the serial library
Serial serial;//Create Serial objects myPoart 
int data;

void setup()
{
   size(600,500);
   noStroke();
   smooth();
   // Open the serial port and set the baud rate to 9600
   // This experiment arduino board is connected to COM17, here please
   // adjust according to actual situation.
   serial = new Serial(this, "COM17", 9600); 
}

void draw()
{
   background(255,255,255);     
   fill(255,0,0);
   ellipse(232,282,200,200);
   fill(0,255,0);
   ellipse(328,184,200,200);
   fill(0,0,255);
   ellipse(368,318,200,200);
}

void mousePressed()
{    
  int imgC = get(mouseX,mouseY);  
  int R = (imgC >> 16) & 0xFF; 
  int G = (imgC >> 8) & 0xFF; 
  int B = imgC & 0xFF;
  println("Current position color: Red = "+R+", Green = "+G+", Blue = "+B);  
  serial.write('R');
  serial.write(R);
  serial.write('G');
  serial.write(G);
  serial.write('B');
  serial.write(B);
  
}