// C++ code
//
#include<LiquidCrystal.h>
int rs=12,en=11,d1=5,d2=4,d3=3,d4=2;
LiquidCrystal lcd(rs,en,d1,d2,d3,d4);
int sensorPin = 0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
}
void loop()
{
 int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0); 
  
  
  float temp = (voltage * 1000 - 500) / 10; 
  /*
  float voltage = sensorValue * 5.02 / 1023.0; 
  float temp = (voltage - 0.5) * 100;*/
  Serial.print(temp);
  Serial.println(" C");
  lcd.setCursor(0,0);
  lcd.print("Temperature is:");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print("C");
  delay(100);
  
}
