#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Define hardware type and number of matrices
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4  // Number of 8x8 matrices (Change if needed)

#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 10

// Initialize display
MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
    display.begin();  // Start the display
    display.setIntensity(5);  // Set brightness (0-15)
    display.displayClear();  // Clear the screen
    display.displayText("HELLO", PA_CENTER, 100, 1000, PA_PRINT, PA_NO_EFFECT);
}

void loop() {
    display.displayAnimate();  // Keep the text on screen
}

