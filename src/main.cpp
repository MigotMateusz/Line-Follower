#include <Wire.h>
#include "oled.h"
#include "utilities.h"
#include "config.h"
#include "motors.h"

bool isBatteryLevelGood = true;
bool isOnTheLine = true;
lastMove move;
long long previousMillis;

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
  previousMillis = millis();
}

void loop() {
  if(!isBatteryLevelGood) {
    for(;;) {

    }
  }

  int frontSensor = adc1_get_raw(CNY70_FRONT_CHANNEL);

  int centerSensor;
  adc2_get_raw(CNY70_CENTER_CHANNEL, ADC_WIDTH_12Bit, &centerSensor);

  int centerLeftSensor = adc1_get_raw(CNY70_CENTER_LEFT_CHANNEL);

  int leftSensor;
  adc2_get_raw(CNY70_LEFT_CHANNEL, ADC_WIDTH_12Bit, &leftSensor);

  int centerRightSensor = adc1_get_raw(CNY70_CENTER_RIGHT_CHANNEL);

  int rightSensor = adc1_get_raw(CNY70_RIGHT_CHANNEL);

  //FORWARD
  if((frontSensor > BLACK_DECISION_BOUNDARY && centerSensor > BLACK_DECISION_BOUNDARY) || frontSensor > BLACK_DECISION_BOUNDARY) {
    /*forward: 1A Low, 2A High, 4A Low, 3A high*/
    moveForward();
    move = FORWARD;
  } 
  //RIGHT
  else if(centerRightSensor > BLACK_DECISION_BOUNDARY || rightSensor > BLACK_DECISION_BOUNDARY) {
    turnRight();
    move = RIGHT;
  } 
  //LEFT
  else if(centerLeftSensor > BLACK_DECISION_BOUNDARY || leftSensor > BLACK_DECISION_BOUNDARY) {
    turnLeft();
    move = LEFT;
  } 
  //STAY
  else {
    switch(move) {
      case FORWARD:
        moveForward();
        break;
      
      case LEFT:
        turnLeft();
        break;

      case RIGHT:
        turnRight();
        break;

      default:
        stopMotors();
        break;
    }
  }
  //printDebug(move, leftSensor, centerLeftSensor, centerSensor,
  //centerRightSensor, rightSensor, frontSensor);

  long long currentMillis = millis();
  if(currentMillis - previousMillis > 2000) {
    previousMillis = currentMillis;
    readMPU();
    printCalcGyroData();
  }
}