#include <LiquidCrystal.h>

// LCD pins: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const float Rs = 1.0;   // Shunt resistor (ohms)
const float Vcc = 3.3;  // Supply voltage changed to 3.3V
float energy_mWh = 0;
unsigned long lastMillis = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Power Monitor");
  delay(1500);
  lcd.clear();
  
  Serial.begin(9600);
  Serial.println("Time(s)\tPower(mW)\tEnergy(mWh)");
  
  lastMillis = millis();
}

void loop() {
  // Simulated sensor: potentiometer on A0
  int adcNode = analogRead(A0);
  float Vnode = (adcNode * Vcc) / 1023.0;

  float Vshunt = Vnode;        // drop across shunt
  float I = Vshunt / Rs;       // current
  float Vload = Vcc - Vnode;   // voltage across load
  float P = Vload * I;         // instantaneous power (W)

  unsigned long now = millis();
  float dt = (now - lastMillis) / 1000.0; // time in sec
  lastMillis = now;

  energy_mWh += (P * 1000.0) * (dt / 3600.0);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("P=");
  lcd.print(P * 1000.0, 1); // mW
  lcd.print(" mW     ");

  lcd.setCursor(0, 1);
  lcd.print("E=");
  lcd.print(energy_mWh, 2);
  lcd.print(" mWh   ");

  // Log data to Serial
  Serial.print(now / 1000.0, 1); Serial.print("\t");
  Serial.print(P * 1000.0, 1);   Serial.print("\t");
  Serial.println(energy_mWh, 2);

  delay(1000); // 1-second logging interval
}
