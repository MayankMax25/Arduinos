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
  lcd.setCursor(0, 0);
  lcd.print("Name: ");
}

void loop()

{
  lcd.setCursor(0, 1);
  lcd.print("Mayank Pal");
  /*lcd.noBlink();//Disables cursor blinking on the LCD.
  delay(3000);
  lcd.blink();//Enables cursor blinking on the LCD.
  delay(3000);*/
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(200);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  /*for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(250);
  }*/

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(200);}
}