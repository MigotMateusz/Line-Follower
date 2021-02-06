#include <Arduino.h>
#include <driver/adc.h>
#define voltageDivider 39

double batteryVoltage;

bool checkBatteryLevel() {
    Serial.begin(9600);
    int batteryValue = adc1_get_raw(ADC1_CHANNEL_3);
    //1V gives ~313 on adc
    Serial.println(batteryValue);
    Serial.println("---");
    batteryVoltage = batteryValue * 313 / 100000;

    if(batteryValue > 1800)
        return true;
    
    return false;
}

double getBatteryVoltage() {
    return batteryVoltage;
}
