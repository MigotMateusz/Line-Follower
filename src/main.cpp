#include <Wire.h>
#include "oled.h"
#include "utilities.h"
#include "config.h"

bool isBatteryLevelGood = true;
bool isOnTheLine = true;

void setup() {
  Serial.begin(9600);

  setupDisplay();
  setupADC();
  setupMotorPins();
  setupMPU();

  isBatteryLevelGood = checkBatteryLevel();

  if(/*isBatteryLevelGood*/ true) {
    double batteryLevel = getBatteryVoltage();
    Serial.println("Battery Lvl Good");
    Serial.println(batteryLevel);
    printBatteryLevel(batteryLevel);
    printBatteryGood();
    delay(5000);

    isBatteryLevelGood = true;

    isOnTheLine = checkIfOnTheLine();
    if(/*isOnTheLine*/true)
      printStartUpSuccess();
    
    else {
      printStartUpFailure();
      while(!isOnTheLine) {
        isOnTheLine = checkIfOnTheLine();
        delay(3000);
      }
      printStartUpSuccess();
    }
      
  } else {
    double batteryLevel = getBatteryVoltage();
    printBatteryLevel(batteryLevel);
    printBatteryWarning();
    Serial.println("Battey Lvl Bad");
    Serial.println(batteryLevel);
  }
}

void loop() {
  if(!isBatteryLevelGood) {
    for(;;) {

    }
  }

  int frontSensor = adc1_get_raw(CNY70_FRONT_CHANNEL);
  Serial.print("Front: ");
  Serial.println(frontSensor);

  int centerSensor = adc1_get_raw(CNY70_CENTER_CHANNEL);
  Serial.print("Center: ");
  Serial.println(centerSensor);

  int centerLeftSensor;
  adc2_get_raw(CNY70_CENTER_LEFT_CHANNEL, ADC_WIDTH_12Bit, &centerLeftSensor);
  Serial.print("Center-left: ");
  Serial.println(centerLeftSensor);

  int leftSensor = adc1_get_raw(CNY70_LEFT_CHANNEL);
  Serial.print("Left: ");
  Serial.println(leftSensor);

  int centerRightSensor = adc1_get_raw(CNY70_CENTER_RIGHT_CHANNEL);
  Serial.print("Center-right: ");
  Serial.println(centerRightSensor);

  int rightSensor;
  adc2_get_raw(CNY70_RIGHT_CHANNEL, ADC_WIDTH_12Bit, &rightSensor);
  Serial.print("Right: ");
  Serial.println(rightSensor);

  Serial.println("---");
  Serial.println("---");
  Serial.println("---");
  
  delay(2000);
  readMPU();
  printCalcGyroData();
  //printAccGyroData();
  /*digitalWrite(motor3A, HIGH);
  digitalWrite(motor4A, LOW);
  delay(2000);
  digitalWrite(motor4A, LOW);*/
  
}