// C++ code
#include <LiquidCrystal.h>
//
int rs=12,en=11,d4=5,d5=4,d6=3,d7=2;
/*rs, en, d4-d7 are pins on the Arduino 
which connect to control pins on the LCD.*/
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//rs stands for register select.
//en stands for enable.
//d4-d7 are data pins.
void setup()
{
  lcd.begin(16,2);
  lcd.print("Hello World!");
  /*Prints "Hello World!" on the LCD screen, 
  starting at the first position of the first row.*/
}

void loop()
{
  lcd.noBlink();//Disables cursor blinking on the LCD.
  delay(3000);
  lcd.blink();//Enables cursor blinking on the LCD.
  delay(3000);
}