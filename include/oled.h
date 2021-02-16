#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_I2CDevice.h>
#include "gyro.h"
#include "config.h"

//SID, SCLK, DC, RST, CS
Adafruit_SH1106 display(16,23,4,-1,15);


void setupDisplay() {
    display.begin(SH1106_SWITCHCAPVCC);
    display.display();
    delay(2000);
    display.clearDisplay();
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
    display.display();
}

void printBatteryGood() {
    display.clearDisplay();
    display.drawPixel(10, 10, WHITE);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.setTextSize(1.5);
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
    display.println(AccY);
    display.print(" Z: ");
    display.println(AccZ);

    display.println("Gyroscope");
    display.print("X: ");
    display.print(GyroX);
    display.print(" Y: ");
    display.println(GyroY);
    display.print(" Z: ");
    display.println(GyroZ);

    display.display();
}

void printCalcGyroData() {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    //pl. Przechył
    display.print("Roll: ");
    display.println(roll);
    //pl. Pochylenie
    display.print("Pitch: ");
    display.println(pitch);
    //pl. Kierunek azymutalny
    display.print("Yaw: ");
    display.println(yaw);

    display.display();
}

void printDebug(lastMove move, int ll, int l, int c, int r, int rr, int f) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    switch(move) {
        case FORWARD:
            display.println("FORWARD");
        break;
      
      case LEFT:
        display.println("LEFT");
        break;

      case RIGHT:
        display.println("RIGHT");
        break;

      default:
        display.println("DEFAULT");
        break;
    }
    display.print("Front: ");
    display.println(f);
    display.print("c: ");
    display.print(c);
    display.print(" l: ");
    display.print(ll);
    display.print(" cl: ");
    display.println(l);
    display.print("cr: ");
    display.print(r);
    display.print(" r: ");
    display.print(rr);
    display.display();
}

#endif