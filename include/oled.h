#include <Arduino.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_I2CDevice.h>
#include "gyro.h"

//SID, SCLK, DC, RST, CS
Adafruit_SH1106 display(16,23,4,-1,15);


void setupDisplay() {
    display.begin(SH1106_SWITCHCAPVCC);
    display.display();
    delay(2000);
    display.clearDisplay();
}

void draw(void) {
     //display.begin(SH1106_SWITCHCAPVCC);
    //display.display();
    //delay(2000);
    

    // Clear the buffer.
    display.clearDisplay();
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

void printBatteryLevel(double level) {
    display.clearDisplay();
     display.drawPixel(10, 10, WHITE);
     display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("Battery level: ");
    display.print(level);
    display.println("V");
    display.display();
    
}

void printBatteryWarning() {
    display.println("");
    display.setTextSize(3);
    display.println("WARNING");
    display.setTextSize(1);
    display.println("Battery voltage is");
    display.println("too low. Please");
    display.println("recharge batteries");
    //display.println("Please recharge batteries");
    display.display();
}

void printBatteryGood() {
    display.println("Battery level is good");
    display.println("Device will move soon");
    display.display();
}

void printStartUpSuccess() {
    
    for(int i = 5; i >=1; i--) {
        display.clearDisplay();
        display.setTextSize(3);
        display.print(i);
        display.display();
        delay(1000);
    }
    display.clearDisplay();
    display.print("GO");
    display.display();
    
}

void printStartUpFailure() {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println("Please put the robot");
    display.println("on the start");
    display.display();
}

void printAccGyroData() {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println("Accelerometer");
    display.print("X: ");
    display.print(AccX);
    display.print(" Y: ");
    display.print(AccY);
    display.print(" Z: ");
    display.println(AccZ);

    display.println("Gyroscope");
    display.print("X: ");
    display.print(GyroX);
    display.print(" Y: ");
    display.print(GyroY);
    display.print(" Z: ");
    display.println(GyroZ);

    display.display();
}