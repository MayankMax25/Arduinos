#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address — most common are 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int correctCode = 1234;
const int greenLed = 8;
const int redLed = 9;
const int buzzer = 10;   // 🔔 Buzzer connected to digital pin 10

String inputCode = "";

void setup() {
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  digitalWrite(buzzer, LOW);

  // Initialize I2C LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LAB DOOR LOCK");
  lcd.setCursor(0, 1);
  lcd.print("Enter 4-digit:");

  Serial.println("=== LAB DOOR SECURITY SYSTEM ===");
  Serial.println("Enter 4-digit passcode:");
  Serial.print("> ");
}

void loop() {
  if (Serial.available()) {
    inputCode = Serial.readStringUntil('\n');
    inputCode.trim();

    lcd.clear();
    lcd.print("Entered: ");
    lcd.print(inputCode);

    // Validate input length
    if (inputCode.length() != 4) {
      Serial.println("\n❌ Passcode must be exactly 4 digits!");
      lcd.setCursor(0, 1);
      lcd.print("Invalid Length!");
      buzzError();
      delay(2000);
      resetSystem();
      return;
    }

    // Validate all digits
    for (int i = 0; i < 4; i++) {
      if (!isDigit(inputCode.charAt(i))) {
        Serial.println("\n❌ Invalid Input! Only digits allowed.");
        lcd.setCursor(0, 1);
        lcd.print("Invalid Input!");
        buzzError();
        delay(2000);
        resetSystem();
        return;
      }
    }

    int entered = inputCode.toInt();
    Serial.print("You entered: ");
    Serial.println(inputCode);

    lcd.clear();
    lcd.print("Code: ");
    lcd.print(inputCode);
    lcd.setCursor(0, 1);

    if (entered == correctCode) {
      Serial.println("✅ Access Granted!");
      lcd.print("ACCESS GRANTED");
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
    } else {
      Serial.println("❌ Wrong Code!");
      lcd.print("ACCESS DENIED");
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      buzzError();
    }

    delay(3000);
    resetSystem();
  }
}

void resetSystem() {
  inputCode = "";
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  digitalWrite(buzzer, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LAB DOOR LOCK");
  lcd.setCursor(0, 1);
  lcd.print("Enter 4-digit:");

  Serial.println();
  Serial.println("=== Lab Door Locked ===");
  Serial.println("Enter 4-digit passcode:");
  Serial.print("> ");
}

// 🔔 Function to make buzzer sound for invalid or wrong codes
void buzzError() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
}

