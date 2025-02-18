// C++ code
#include <LiquidCrystal.h>
//
int rs=12,en=11,d4=5,d5=4,d6=3,d7=2;
/*rs, en, d4-d7 are pins on the Arduino 
which connect to control pins on the LCD.*/
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
String first = "Hello World!";
String second = "Scrolling";
int textLength = second.length();
int lcdColumns = 16;
//rs stands for register select.
//en stands for enable.
//d4-d7 are data pins.
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(first);
  
  
}

void loop()
{
  for (int i = 0; i < textLength + lcdColumns; i++) {
    lcd.setCursor(0,1);
    lcd.print("                ");
    //lcd.clear();
    lcd.setCursor(max(0, lcdColumns - i), 1);
    lcd.print(second.substring(max(0, i - lcdColumns), i));
    delay(300);
  }
  
  delay(1000);
}