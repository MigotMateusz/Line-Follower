#ifndef UTILITIES_H
#define UTILITIES_H

#include "config.h"

double batteryVoltage;
double stackVoltage;

bool checkBatteryLevel() {
    Serial.begin(9600);
    int batteryValue = adc1_get_raw(VOLTAGE_DIVIDER_ADC_CHANNEL);
    //1V gives ~313 on adc
    Serial.print("Battery value from ADC: ");
    Serial.println(batteryValue);
    Serial.println("---");
    batteryVoltage = batteryValue / 313.0;

    double stackVoltage1pom = batteryValue * (3.3 / 4095.0f);
    stackVoltage = stackVoltage1pom * 4;
    Serial.print("Stack voltage: ");
    Serial.println(stackVoltage);


    if(batteryValue > 1878)
        return true;
    
    return false;
}

double getBatteryVoltage() {
    return batteryVoltage;
}

bool checkIfOnTheLine() {
    int frontValue = adc1_get_raw(CNY70_FRONT_CHANNEL);
    int centerValue;
    adc2_get_raw(CNY70_CENTER_CHANNEL, ADC_WIDTH_12Bit, &centerValue);
    
    if(frontValue > BLACK_DECISION_BOUNDARY 
        && centerValue > BLACK_DECISION_BOUNDARY)
        return true;

    else 
        return false;
}



#endif