#ifndef UTILITIES_H
#define UTILITIES_H

#include "config.h"

double batteryVoltage;

bool checkBatteryLevel() {
    Serial.begin(9600);
    int batteryValue = adc1_get_raw(VOLTAGE_DIVIDER_ADC_CHANNEL);
    //1V gives ~313 on adc
    Serial.print("Battery value from ADC: ");
    Serial.println(batteryValue);
    Serial.println("---");
    batteryVoltage = batteryValue / 313.0;

    if(batteryValue > 1800)
        return true;
    
    return false;
}

double getBatteryVoltage() {
    return batteryVoltage;
}

bool checkIfOnTheLine() {
    int frontValue = adc1_get_raw(CNY70_FRONT_CHANNEL);
    int centerValue;// = adc1_get_raw(CNY70_CENTER_CHANNEL);
    adc2_get_raw(CNY70_CENTER_CHANNEL, ADC_WIDTH_12Bit, &centerValue);
    Serial.print("Front: ");
    Serial.println(frontValue);
    Serial.print("Center: ");
    Serial.println(centerValue);
    
    if(frontValue > BLACK_DECISION_BOUNDARY 
        && centerValue > BLACK_DECISION_BOUNDARY)
        return true;

    else 
        return false;
}



#endif