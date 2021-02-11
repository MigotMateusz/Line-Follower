#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <cmath>

const int MPU = 0x68;
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX = 0, accAngleY = 0, gyroAngleX = 0, gyroAngleY = 0, gyroAngleZ = 0;
float roll = 0, pitch = 0, yaw = 0;
float AccErrorX = 0, AccErrorY = 0, GyroErrorX = 0, GyroErrorY = 0, GyroErrorZ = 0;
float elapsedTime=0, currentTime=0, previousTime=0;
int c = 0;
double pi = 3.14159265;

void setupMPU() {
  Serial.begin(9600);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  delay(20);
}

void readMPU() {
    // === Read acceleromter data === //
  Serial.begin(9600);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value

  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  
  Serial.println("Accelerometr Readings");
  Serial.print("X: ");
  Serial.println(AccX);
  Serial.print("Y: ");
  Serial.println(AccY);
  Serial.print("Z: ");
  Serial.println(AccZ);
  Serial.println("Gyroscope Readings");
  Serial.print("X: ");
  Serial.println(GyroX);
  Serial.print("Y: ");
  Serial.println(GyroY);
  Serial.print("Z: ");
  Serial.println(GyroZ);

  pitch = 180 * atan(AccX/sqrt(AccY*AccY + AccZ*AccZ))/pi;
  roll = 180 * atan(AccY/sqrt(AccX*AccX + AccZ*AccZ))/pi;
  yaw = 180 * tan(AccZ/sqrt(AccX*AccX + AccZ*AccZ))/pi;

  // Print the values on the serial monitor
  Serial.print("Roll: ");
  Serial.println(roll);
  Serial.print("Pitch: ");
  Serial.println(pitch);
  Serial.print("Yaw: ");
  Serial.println(yaw);
}

#endif