#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("Enter text:");
}

void loop() {
    if (Serial.available()) {
        lcd.clear();
        String text = Serial.readStringUntil('\n');
        lcd.setCursor(0, 0);
        lcd.print(text.substring(0, 16)); // First line
        if (text.length() > 16) {
            lcd.setCursor(0, 1);
            lcd.print(text.substring(16, 32)); // Second line
        }
    }
}