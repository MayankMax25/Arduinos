#include <Wire.h>
#include <U8g2lib.h>

// Initialize OLED for SSH1136 using U8g2 library (I2C)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
//U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
    u8g2.begin();
}

void loop() {
    /*u8g2.clearBuffer();
    //u8g2.setFont(u8g2_font_ncenB08_tr); 
    //u8g2.setFont(u8g2_font_ncenB14_tr);
    //u8g2.setFont(u8g2_font_helvB10_tr);
    u8g2.setFont(u8g2_font_lubB14_tr);  // Select font
    u8g2.drawStr(5, 49, "Hello World");  // Display text
    u8g2.sendBuffer();
    delay(1000);*/
    //u8g2.clearBuffer();

    // Small text
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(10, 10, "Small Font");

    // Medium text
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(10, 30, "Medium Font");

    // Large text
    u8g2.setFont(u8g2_font_helvB18_tr);
    u8g2.drawStr(10, 55, "BIG TEXT!");

    u8g2.sendBuffer();
    delay(2000);
}
/*
#include <Wire.h>
#include <U8g2lib.h>

// Initialize for SSH1136 OLED (I2C)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ //U8X8_PIN_NONE);
/*
void setup() {
    u8g2.begin();
}

void loop() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(10, 40, "OLED Test OK!");
    u8g2.sendBuffer();
    delay(1000);
}*/
