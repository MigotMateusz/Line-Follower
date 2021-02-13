#ifndef MOTORS_H
#define MOTORS_H
#include "config.h"

void moveForward() {
    ledcWrite(0, 195);
    ledcWrite(1, 195);
    digitalWrite(motor1A, LOW);
    digitalWrite(motor3A, LOW);
    digitalWrite(motor4A, HIGH);
    digitalWrite(motor2A, HIGH);
}

void turnLeft() {
    ledcWrite(1, 0);
    ledcWrite(0, 183);
    digitalWrite(motor3A, LOW);
    digitalWrite(motor4A, LOW);
    digitalWrite(motor1A, LOW);
    digitalWrite(motor2A, HIGH);
}

void turnRight() {  
    ledcWrite(0, 0);
    ledcWrite(1, 183);
    digitalWrite(motor3A, LOW);
    digitalWrite(motor4A, HIGH);
    digitalWrite(motor1A, LOW);
    digitalWrite(motor2A, LOW);
}

void stopMotors() {
    ledcWrite(0,0);
    ledcWrite(1,0);
    digitalWrite(motor1A, LOW);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor4A, LOW);
    digitalWrite(motor3A, LOW);
}

#endif