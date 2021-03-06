/***********************************************************
File name:   AdeeptSnakeGame.ino
Press the button 1 to control the game level 1 ~ 6; button 2 control into the game;
When entering the game, the four buttons were controlled snake up and down to move 
around; after the game press the button 4 to start the game
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/01/04 
***********************************************************/
#include "U8glib.h"
#include <EEPROM.h>

// 8Bit Com: D0..D7: 4,5,6,7, 8,9,10,11, en=A4, RS=A3,rw=A2
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7, 8, 9, 10, 11, 18, 17, 16);   
int blueButton1Pin=13;   //Set the digital 13 to blue 1 button module interface 
int blueButton2Pin=12;   //Set the digital 12 to blue 2 button module interface 
int redButtonPin=1;      //Set the digital 1 to red button module interface 
int whiteButtonPin=0;    //Set the digital 0 to white button module interface 

static unsigned char snake[] U8G_PROGMEM ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,
0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x07,
0x80,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x07,
0xC0,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x07,
0xC0,0xFF,0x37,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0x0F,
0xE0,0xE3,0x3F,0x7C,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xCE,0xFF,0xCF,0x0F,
0xF0,0x01,0x7F,0xFC,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0xFC,0xCF,0x7F,0x80,0x0F,
0xF0,0x01,0x7E,0xFC,0x07,0xFC,0x01,0x00,
0x02,0x80,0xFF,0xFC,0xCF,0x3F,0x00,0x0F,
0xF0,0x00,0x7C,0xE0,0x07,0xFC,0x0F,0xC0,
0x03,0xE0,0xFF,0xFC,0x07,0x3E,0x00,0x1E,
0xF0,0x00,0x7C,0xE0,0x0F,0xFC,0x0F,0xE0,
0x07,0xE0,0xFF,0xF0,0x01,0x3E,0x00,0x1E,
0xF0,0x00,0x78,0xE0,0x0F,0xE0,0x05,0xE0,
0x07,0x00,0x1F,0xF0,0x00,0x3E,0x00,0x1C,
0xF0,0x00,0x78,0xE0,0x1F,0xE0,0x00,0xE0,
0x07,0x00,0x1F,0x78,0x00,0x3E,0x00,0x04,
0xF0,0x00,0x70,0xE0,0x1F,0xE0,0x00,0xF0,
0x07,0x00,0x1F,0x78,0x00,0x3E,0x00,0x00,
0xF0,0x00,0x70,0xE0,0x3F,0xE0,0x00,0xF0,
0x0F,0x00,0x1F,0x3C,0x00,0x3E,0xE0,0x00,
0xF0,0x01,0x20,0xE0,0x3F,0xE0,0x00,0xF0,
0x0F,0x00,0x1F,0x1E,0x00,0x3E,0xE0,0x00,
0xF0,0x01,0x00,0xE0,0x7F,0xE0,0x00,0xF8,
0x0F,0x00,0x1F,0x1E,0x00,0x3E,0xE0,0x00,
0xF0,0x03,0x00,0xE0,0x7C,0xE0,0x00,0x78,
0x1F,0x00,0x1F,0x0F,0x00,0x3E,0xE0,0x00,
0xF0,0x0F,0x00,0xE0,0xFC,0xE0,0x00,0x38,
0x1F,0x00,0x9F,0x07,0x00,0x3E,0xE0,0x00,
0xE0,0x1F,0x00,0xE0,0xF8,0xE0,0x00,0x3C,
0x1F,0x00,0x9F,0x07,0x00,0x3E,0xE0,0x00,
0xC0,0x7F,0x00,0xE0,0xF8,0xE1,0x00,0x3C,
0x1F,0x00,0xDF,0x03,0x00,0x3E,0xF0,0x00,
0xC0,0xFF,0x00,0xE0,0xF0,0xE1,0x00,0x3C,
0x3E,0x00,0xFF,0x07,0x00,0xFE,0xFF,0x00,
0x00,0xFF,0x03,0xE0,0xF0,0xE3,0x00,0x1C,
0x3E,0x00,0xFF,0x07,0x00,0xFE,0xFF,0x00,
0x00,0xFE,0x07,0xE0,0xE0,0xE3,0x00,0x1E,
0x3E,0x00,0xFF,0x0F,0x00,0xFE,0xFF,0x00,
0x00,0xFC,0x1F,0xE0,0xE0,0xE7,0x00,0x1E,
0x7C,0x00,0xFF,0x0F,0x00,0x7E,0xF8,0x00,
0x00,0xF0,0x3F,0xE0,0xC0,0xEF,0x00,0x0E,
0x7C,0x00,0xBF,0x1F,0x00,0x3E,0xF0,0x00,
0x00,0xC0,0x3F,0xE0,0x80,0xEF,0x00,0xFF,
0x7F,0x00,0x1F,0x1F,0x00,0x3E,0xE0,0x00,
0x00,0x80,0x7F,0xE0,0x80,0xFF,0x00,0xFF,
0x7F,0x00,0x1F,0x3F,0x00,0x3E,0xE0,0x00,
0x00,0x00,0x7E,0xE0,0x00,0xFF,0x00,0xFF,
0xFF,0x00,0x1F,0x3E,0x00,0x3E,0xE0,0x00,
0x00,0x00,0xFC,0xE0,0x00,0xFF,0x00,0x07,
0xF8,0x00,0x1F,0x7E,0x00,0x3E,0xE0,0x00,
0x00,0x00,0xF8,0xE0,0x00,0xFE,0x80,0x07,
0xF8,0x00,0x1F,0x7C,0x00,0x3E,0xE0,0x00,
0x00,0x00,0xF8,0xE0,0x00,0xFE,0x80,0x07,
0xF8,0x00,0x1F,0xFC,0x00,0x3E,0x00,0x00,
0x20,0x00,0xF0,0xE0,0x00,0xFC,0x80,0x03,
0xF8,0x01,0x1F,0xF8,0x00,0x3E,0x00,0x00,
0x38,0x00,0xF0,0xE0,0x00,0xFC,0xC0,0x03,
0xF0,0x01,0x1F,0xF8,0x01,0x3E,0x00,0x00,
0x78,0x00,0xF0,0xE0,0x00,0xF8,0xC0,0x03,
0xF0,0x01,0x1F,0xF0,0x01,0x3E,0x00,0x00,
0x78,0x00,0xF8,0xE0,0x00,0xF0,0xC0,0x03,
0xF0,0x03,0x1F,0xF0,0x01,0x3E,0x00,0x18,
0x78,0x00,0xF8,0xE0,0x00,0xF0,0xE0,0x03,
0xF8,0x03,0x1F,0xE0,0x03,0x3E,0x00,0x1C,
0x70,0x00,0x78,0xE0,0x00,0xE0,0xF8,0x0F,
0xFC,0xEF,0x3F,0xE0,0x03,0x3E,0x00,0x1C,
0xF0,0x00,0x7C,0xE0,0x0F,0xE0,0xF8,0x0F,
0xFC,0xEF,0xFF,0xF8,0x07,0x3E,0x00,0x1E,
0xF0,0x00,0x3C,0xFC,0x0F,0xC0,0xF8,0x01,
0xC0,0xEF,0xFF,0xF8,0x1F,0x3E,0x00,0x1E,
0xF0,0x01,0x3E,0xFC,0x0F,0x00,0x00,0x00,
0x00,0x00,0xC0,0xF8,0xDF,0x3F,0x00,0x1F,
0xF0,0x87,0x1F,0xFC,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0xDF,0xFF,0x83,0x0F,
0xF0,0xFF,0x0F,0x04,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0x0F,
0xF0,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0x0F,
0xF0,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x0F,
0xE0,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x0F,
0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x07,
0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//bitmap“SNAKE”
int level; //Snake Game level

//The corresponding game level, the snake to move a lattice 
//required time (actually slightly larger than leveltime)（ms）
int leveltime;

unsigned long time1=0;//Record system time
 char r[3];//The game ends to display the highest score
 char u[3];//The game ends to display the current score
unsigned long time=0;//Record system time
int n=0;//The current snake length
int wei=0;//Records snake tail coordinates: 0 ~ 511
int ore;//Direction of movement of the snake 1: Right 2: Up 3: Left 4: Down
int y;

//From k [0] to k [511] in order to store the coordinates of the snake head 
//to the tail, if there is no save -1
int k[512];
//For example, if the snake has two nodes, the snake head coordinate is 1 
//and the tail coordinates is 0, K [1] = 0, k [2] ~ k [511] = - 1 

int addr=0;//EEPROM stores the highest address
unsigned long s[16];//Used to record the coordinates of each section of the snake is occupied
long randNumber;//Randomly produces a snack food as a snake
unsigned long p,q;

void draw1(void)
{

    r[0]=(EEPROM.read(addr)-3)/100+48;
    r[1]=((EEPROM.read(addr)-3)%100)/10+48;
    r[2]=(EEPROM.read(addr)-3)%10+48;
    u[0]=(n-3)/100+48;;
    u[1]=((n-3)%100)/10+48;
    u[2]=(n-3)%10+48;
    u8g.setFont(u8g_font_helvB24);
    u8g.drawStr(74, 28,r);
    u8g.setFont(u8g_font_helvB24);
    u8g.drawStr(74, 60,u );
    u8g.drawHLine(0,32, 128);
    u8g.setFont(u8g_font_helvB12);
    u8g.drawStr(4,15,"HIGH");
    u8g.drawStr(4,31,"SCORE");
    u8g.drawStr(4,47,"YOUR");
    u8g.drawStr(4,63,"SCORE");
}
void draw2(void)
{
u8g.setFont(u8g_font_helvB12);
u8g.drawStr(42, 32,"GAME");
u8g.drawStr(42, 46,"OVER");
u8g.drawRFrame(39,17, 53,32, 2);
}
void draw(void) {
  int x;
int m=0;
  for(x=0;x<=511;x++)
  {
  if(k[x]>=0)
  {
    m=m+1;     
  }
  }
 for(x=0;x<=m;x++)
  {
  if((k[x]-k[x+1])*(k[x]-k[x+1])==1)
  {
  u8g.drawBox((min(k[x],k[x+1])%32)*4,(min(k[x],k[x+1])/32)*4,7,3);
  }
  }
   for(x=0;x<=m-2;x++)
  {
  if((k[x]-k[x+1])*(k[x]-k[x+1])==1024)
  {
  u8g.drawBox((min(k[x],k[x+1])%32)*4,(min(k[x],k[x+1])/32)*4,3,7);
  }
  }
u8g.drawBox((randNumber%32)*4,(randNumber/32)*4,3,3);  
//Serial.println(randNumber);
}
unsigned long cifang(int w)//2 of the w power
{
      int v;
      if(w<=30)
      {
    unsigned long q=1;
    for(v=0;v<=w;v++)
    {
    q=q*2;
    }
    unsigned long p=q/2;
    return p;
      }
      if(w==31)
      {
      p=2147483648;
      return p;
      }

}

void writes()
{
  for(y=0;y<=15;y++)   
{
s[y]=0;
}
  for(y=0;y<n;y++)
  {
  s[k[y]/32]=s[k[y]/32]+cifang(31-k[y]%32);
  }
}
void gameover()
{
    if(n>EEPROM.read(addr))
      {
      EEPROM.write(addr, n);//If the score exceeds the highest score, the record
      }
       u8g.firstPage();  
      do {
     draw2();//Display GAME OVER
      } while( u8g.nextPage() );
      delay(1500);
      u8g.firstPage();  
      do {
     draw1();//Displays the score
      } while( u8g.nextPage() );
        for(y=0;y<=511;y++)//The game ends with reinitialization to start over
    {
    k[y]=-1;
    }
      k[0]=240;
      k[1]=239;
      k[2]=238;
    for(y=0;y<=15;y++)   
    {
    s[y]=0;
    }
    for(y=0;y<=511;y++)
      {
      if(k[y]>=0)
      {
      s[k[y]/32]=s[k[y]/32]+cifang(31-k[y]%32);
      }
      }
    ore=1;
}

int le(int w)//Level w corresponding to the delay
{
    int f;
    if(w==1) f=900;
    if(w==2) f=500;
    if(w==3) f=250;
    if(w==4) f=100;
    if(w==5) f=50;
    if(w==6) f=2;
    return f;
}



void setup(void) {
int level=EEPROM.read(1);
    pinMode(blueButton1Pin,INPUT); //Set digital 13 port mode, the INPUT for the input
    pinMode(blueButton2Pin,INPUT); //Set digital 12 port mode, the INPUT for the input
    pinMode(redButtonPin,INPUT);   //Set digital 1 port mode, the INPUT for the input
    pinMode(whiteButtonPin,INPUT); //Set digital 0 port mode, the INPUT for the input
while(digitalRead(redButtonPin))//analogRead(1)<1000
{
  while(millis()-time1==300)
  {
if(digitalRead(blueButton1Pin)==LOW)//analogRead(0)>900)
{
  level=level+1;
  if(level>6)
  {
  level=1;
  }
}
if(digitalRead(blueButton2Pin)==LOW)//analogRead(0)<100)
{
  level=level-1;
  if(level<1)
  {
  level=6;
  }
}
u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_helvB12);
    switch(level)
    {
    case 1:
     u8g.drawStr(32, 60,"LEVEL 1");
     break;
     case 2:
     u8g.drawStr(32, 60,"LEVEL 2");
     break;
     case 3:
     u8g.drawStr(32, 60,"LEVEL 3");
     break;
     case 4:
     u8g.drawStr(32, 60,"LEVEL 4");
     break;
     case 5:
     u8g.drawStr(32, 60,"LEVEL 5");
     break;
     case 6:
     u8g.drawStr(32, 60,"LEVEL 6");
     break;
    }
    u8g.drawXBMP( 0, 0, 128, 56, snake);
 //   u8g.setFont(u8g_font_helvB24);
 //   u8g.drawStr(12, 40,"SNAKE");
  } while( u8g.nextPage() );
  time1=millis();
  }
}
leveltime=le(level);
if(level!=EEPROM.read(1))
{
EEPROM.write(1,level);
}
  for(y=0;y<=511;y++)   
{
k[y]=-1;
}
  k[0]=240;
  k[1]=239;
  k[2]=238;
for(y=0;y<=15;y++)   
{
s[y]=0;
}
for(y=0;y<=511;y++)
  {
  if(k[y]>=0)
  {
  s[k[y]/32]=s[k[y]/32]+cifang(31-k[y]%32);
  }
  }
randomSeed(analogRead(5));
ore=1;
// attachInterrupt(0, downleft, CHANGE);
//  attachInterrupt(1, upright, CHANGE);
}



void loop(void) {
aa: do {randNumber=random(0,512);}
while(((s[randNumber/32])/(cifang(31-randNumber%32)))%2==1);
 n=0;
  for(y=0;y<=511;y++)
  {
  if(k[y]>=0)
  {
    n=n+1;     
  }
  }

while(k[0]!=randNumber)
{
 
  u8g.firstPage();  
  do {
 draw();
  } while( u8g.nextPage() );
  time=millis();
  while(millis()-time<leveltime)
{
if (digitalRead(blueButton1Pin)==LOW)//analogRead(0)>900)
{
if((ore==1)||(ore==3))  
{
  ore=4;
  goto out;
}
}
if (digitalRead(blueButton2Pin)==LOW)//analogRead(0)<100)
{
if((ore==1)||(ore==3))  
{
  ore=2;
  goto out;
}
}
if (digitalRead(redButtonPin)==LOW)//analogRead(1)>900)
{
if((ore==2)||(ore==4))  
{
  ore=1;
  goto out;
}
}
if (digitalRead(whiteButtonPin)==LOW)//analogRead(1)<100)
{
if((ore==2)||(ore==4))  
{
  ore=3;
  goto out;
}
}
}
out: wei=k[n-1];
  if(ore==1)
  {
  for(y=n-2;y>=0;y--)
  {
  k[y+1]=k[y];
  }
  k[0]=k[0]+1;
   if((k[0]%32==0)||(((s[k[0]/32])/(cifang(31-k[0]%32)))%2==1))   
  {
 gameover();
 while(digitalRead(whiteButtonPin))//analogRead(1)<900)
 {
 }
 goto aa;
  }
 writes();
  }
  if(ore==2)
  {
  for(y=n-2;y>=0;y--)
  {
  k[y+1]=k[y];
  }
  k[0]=k[0]-32;
   if((k[0]<0)||(((s[k[0]/32])/(cifang(31-k[0]%32)))%2==1))   
 {
   gameover();
   while(digitalRead(whiteButtonPin))//analogRead(1)<900)
 {
 }
 goto aa;
  }
 writes();
  }
  if(ore==3)
  {
  for(y=n-2;y>=0;y--)
  {
  k[y+1]=k[y];
  }
  k[0]=k[0]-1;
  if(((k[0]+33)%32==0)||(((s[k[0]/32])/(cifang(31-k[0]%32)))%2==1))
 {
  gameover();
while(digitalRead(whiteButtonPin))//analogRead(1)<900)
 {
 }
 goto aa;
  }
 writes();
  }
  if(ore==4)
  {
  for(y=n-2;y>=0;y--)
  {
  k[y+1]=k[y];
  }
  k[0]=k[0]+32;
   if((k[0]>511)||(((s[k[0]/32])/(cifang(31-k[0]%32)))%2==1))   
 {
  gameover();
  while(digitalRead(whiteButtonPin))//analogRead(1)<900)
 {
 }
 goto aa;
  }
  writes();
  }


}
k[n]=wei;
s[k[n]/32]=s[k[n]/32]+cifang(31-k[n]%32);
}

