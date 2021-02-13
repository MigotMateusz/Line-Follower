#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <driver/adc.h>

#define motor1A 18
#define motor2A 17
#define motorEN12 19

#define motor3A 26
#define motor4A 25
#define motorEN34 27
#define batteryLevelPin 39

#define CNY70_CENTER_LEFT 34 //center-left
#define CNY70_CENTER_LEFT_CHANNEL ADC1_CHANNEL_6

#define CNY70_FRONT 32//front
#define CNY70_FRONT_CHANNEL ADC1_CHANNEL_4

#define CNY70_CENTER 13//center
#define CNY70_CENTER_CHANNEL ADC2_CHANNEL_4

#define CNY70_RIGHT 33 //right
#define CNY70_RIGHT_CHANNEL ADC1_CHANNEL_5

#define CNY70_CENTER_RIGHT 35 //center-right
#define CNY70_CENTER_RIGHT_CHANNEL ADC1_CHANNEL_7

#define CNY70_LEFT 14 //left
#define CNY70_LEFT_CHANNEL ADC2_CHANNEL_6

#define voltageDivider 39
#define VOLTAGE_DIVIDER_ADC_CHANNEL ADC1_CHANNEL_3

#define BLACK_DECISION_BOUNDARY 3900

enum lastMove {
  FORWARD,
  LEFT,
  RIGHT
};



void setupADC() {
  adc1_config_width(ADC_WIDTH_BIT_12);
}

void setupMotorPins() {
    pinMode(motor1A, OUTPUT);
    pinMode(motor2A, OUTPUT);
    pinMode(motorEN12, OUTPUT);
    ledcSetup(0, 30000, 8);
    ledcSetup(1, 30000, 8);
    ledcAttachPin(motorEN12, 0);
    

    pinMode(motor3A, OUTPUT);
    pinMode(motor4A, OUTPUT);
    pinMode(motorEN34, OUTPUT);
    ledcAttachPin(motorEN34, 1);
    //digitalWrite(motorEN12, HIGH);
    //digitalWrite(motorEN34, HIGH);
}

#endif