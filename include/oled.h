#include <Arduino.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_I2CDevice.h>

//SID, SCLK, DC, RST, CS
Adafruit_SH1106 display(16,23,4,-1,15);
//Adafruit_SH1106 display(22,23);


void draw(void) {
    //display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    display.begin(SH1106_SWITCHCAPVCC);
    display.display();
    delay(2000);

    // Clear the buffer.
    display.clearDisplay();
    display.drawPixel(10, 10, WHITE);
     display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Hello, world!");
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println(3.141592);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("0x"); display.println(0xDEADBEEF, HEX);
    display.display();
    delay(2000);
    

}