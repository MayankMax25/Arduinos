#include <GyverOLED.h>

GyverOLED<SSH1106_128x64> oled;
String inputText = ""; // Variable to store user input

void setup() {
  Serial.begin(9600);
  oled.init();  // Initialize OLED
  oled.clear();
  Serial.println("Enter text to display on OLED:");
}

void loop() {
  if (Serial.available()) {  // Check if data is available from Serial
    inputText = Serial.readStringUntil('\n'); // Read input text
    inputText.trim(); // Remove any trailing newlines or spaces
    displayText(inputText); // Call function to display text
  }
}

void displayText(String text) {
  oled.clear();
  oled.setScale(3);
  oled.setCursor(20, 4);
  oled.print(text); // Print user input text
  oled.update();
}