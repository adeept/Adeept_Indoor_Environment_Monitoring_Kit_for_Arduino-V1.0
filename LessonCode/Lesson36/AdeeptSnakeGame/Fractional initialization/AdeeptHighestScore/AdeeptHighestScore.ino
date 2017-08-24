/***********************************************************
File name:   AdeeptHighestScore.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/01/04 
***********************************************************/
#include <EEPROM.h>
void setup()
{
  EEPROM.write(0, 0);//Modify this value to modify the highest score
  EEPROM.write(1, 1);
}

void loop()
{
}
   
