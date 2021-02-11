
#include <Arduino.h>
#include <Wire.h>
#include <driver/adc.h>
#include "oled.h"
#include "utilities.h"

#define motor1A 25
#define motor2A 26
#define motorEN12 27

#define motor3A 26
#define motor4A 25
#define motorEN34 27
#define batteryLevelPin 39

#define CNY70_FRONT 34
#define CNY70_FRONT_CHANNEL ADC1_CHANNEL_6

#define CNY70_CENTER 32
#define CNY70_CENTER_CHANNEL ADC1_CHANNEL_4

#define CNY70_CENTER_LEFT 13
#define CNY70_CENTER_LEFT_CHANNEL ADC2_CHANNEL_4

#define CNY70_CENTER_RIGHT 33
#define CNY70_CENTER_RIGHT_CHANNEL ADC1_CHANNEL_5

#define CNY70_LEFT 35
#define CNY70_LEFT_CHANNEL ADC1_CHANNEL_7

#define CNY70_RIGHT 14
#define CNY70_RIGHT_CHANNEL ADC2_CHANNEL_6


bool isBatteryLevelGood = true;

void setup() {
  setupDisplay();
  //digitalWrite(motor1A, HIGH);
  ////digitalWrite(motor2A, LOW);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motorEN12, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor4A, OUTPUT);
  pinMode(motorEN34, OUTPUT);
  digitalWrite(motorEN12, HIGH);
  digitalWrite(motorEN34, HIGH);
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
}

void loop() {
  if(!isBatteryLevelGood) {
    for(;;) {

    }
  }

  int value = adc1_get_raw(ADC1_CHANNEL_6);
  Serial.print("Front: ");
  Serial.println(value);

  value = adc1_get_raw(CNY70_CENTER_CHANNEL);
  Serial.print("Center: ");
  Serial.println(value);

  adc2_get_raw(CNY70_CENTER_LEFT_CHANNEL, ADC_WIDTH_12Bit, &value);
  Serial.print("Center-left: ");
  Serial.println(value);

  value = adc1_get_raw(CNY70_LEFT_CHANNEL);
  Serial.print("Left: ");
  Serial.println(value);

  value = adc1_get_raw(CNY70_CENTER_RIGHT_CHANNEL);
  Serial.print("Center-right: ");
  Serial.println(value);

  adc2_get_raw(CNY70_RIGHT_CHANNEL, ADC_WIDTH_12Bit, &value);
  Serial.print("Right: ");
  Serial.println(value);
  delay(2000);

  Serial.println("---");
  Serial.println("---");
  Serial.println("---");
  
  //read();
  //printAccGyroData();
  /*digitalWrite(motor3A, HIGH);
  digitalWrite(motor4A, LOW);
  delay(2000);
  digitalWrite(motor4A, LOW);*/
  
}