
#include <Arduino.h>
#include <Wire.h>
#include <driver/adc.h>
#include "oled.h"
//#include "gyro.h"
#include "utilities.h"

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

bool isBatteryLevelGood = true;

void setup() {
  setupDisplay();
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, LOW);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motorEN12, OUTPUT);
  digitalWrite(motorEN12, HIGH);
  Serial.begin(9600);
  setupMPU();
  isBatteryLevelGood = checkBatteryLevel();
  if(/*isBatteryLevelGood*/true) {
    double batteryLevel = getBatteryVoltage();
    Serial.println("good");
    Serial.println(batteryLevel);
    printBatteryLevel(batteryLevel);
    printBatteryGood();
    
    delay(5000);
    isBatteryLevelGood = true;
    //printStartUpFailure();
    printStartUpSuccess();
  } else {
  double batteryLevel = getBatteryVoltage();
    printBatteryLevel(batteryLevel);
    printBatteryWarning();
    Serial.println("bad");
    Serial.println(batteryLevel);
  }
  delay(20);
  //draw();
}

void loop() {
  if(!isBatteryLevelGood) {
    for(;;) {

    }
  }
  int value = adc1_get_raw(ADC1_CHANNEL_6);
  Serial.println(value);
  Serial.println("---");
  delay(2000);
  
  read();
  printAccGyroData();
  //digitalWrite(motor1A, HIGH);
  //digitalWrite(motor2A, LOW);
  //delay(2000);
  //digitalWrite(motor1A, LOW);
  
}