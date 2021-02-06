
#include <Arduino.h>
#include <Wire.h>
#include <driver/adc.h>
#include "oled.h"
#include "gyro.h"

#define motor1A 25
#define motor2A 26
#define motorEN12 27
#define batteryLevelPin 39

/*const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;*/

void setup() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, LOW);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motorEN12, OUTPUT);
  digitalWrite(motorEN12, HIGH);
  Serial.begin(9600);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  /*
  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  delay(20);
  */
  // Call this function if you need to get the IMU error values for your module
  int batteryValue = adc1_get_raw(ADC1_CHANNEL_3);
  Serial.println(batteryValue);
  Serial.println("---");
  delay(20);
  draw();
}

void loop() {
  int value = adc1_get_raw(ADC1_CHANNEL_6);
  Serial.println(value);
  Serial.println("---");
  delay(2000);
  read();
  //digitalWrite(motor1A, HIGH);
  //digitalWrite(motor2A, LOW);
  //delay(2000);
  //digitalWrite(motor1A, LOW);
  
}