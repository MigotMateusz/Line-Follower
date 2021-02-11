#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <Wire.h>

const int MPU = 0x68;
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX = 0, accAngleY = 0, gyroAngleX = 0, gyroAngleY = 0, gyroAngleZ = 0;
float roll = 0, pitch = 0, yaw = 0;
float AccErrorX = 0, AccErrorY = 0, GyroErrorX = 0, GyroErrorY = 0, GyroErrorZ = 0;
float elapsedTime=0, currentTime=0, previousTime=0;
int c = 0;
double pi = 3.141592;

void setupMPU() {
  Serial.begin(9600);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  delay(20);
}

void read() {
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

  
  // Calculating Roll and Pitch from the accelerometer data
  //accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; 
  //accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58;

  accAngleX = atan2(AccX, sqrt(pow(AccY,2) + pow(AccZ,2)))/(pi/180);
  accAngleY = atan2(AccY, sqrt(pow(AccX,2) + pow(AccZ,2)))/(pi/180);
  
  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX = GyroX * elapsedTime; // deg/s * s = deg
  gyroAngleY = GyroY * elapsedTime;
  yaw =   GyroZ * elapsedTime;

  // Complementary filter - combine acceleromter and gyro angle values
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  
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

  // Print the values on the serial monitor
  /*Serial.print("Roll: ");
  Serial.println(roll);
  Serial.print("Pitch: ");
  Serial.println(pitch);
  Serial.print("Yaw: ");
  Serial.println(yaw);*/
}

#endif