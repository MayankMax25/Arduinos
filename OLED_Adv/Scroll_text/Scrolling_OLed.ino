#include <GyverOLED.h>
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER, OLED_SPI, 8, 7, 6> oled;
GyverOLED<SSH1106_128x64> oled;

//char Lorem_ipsum[] = "Lorem ipsum dolor sit amet, лорем ипсум долор сит амет привет народ ё, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip...";
void setup() {
  Serial.begin(9600);
  oled.init();              // инициализация
}

void loop() {
  
  oled.clear();
  uint32_t tmr = millis();
  //oled.autoPrintln(false);
  int val = 128;
  for (;;) {
    oled.clear();
    oled.setScale(2);
    oled.setCursor(val, 4);
    oled.print("Mayank Pal");
    oled.update();
    val--;
    if (millis() - tmr > 20000) return;
  } 
  
}
