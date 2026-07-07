#include <Arduino.h>
#include "config.h"
#include "parking.h"
#include "fire_alarm.h"
#include "parking.h"
#include "lcd_display.h"
#include "gate.h"

bool wasFireDetected = false; 

void setup() {
    Serial.begin(9600);
    initLCD();
    initGate();
    initParking();
    initFireAlarm();
}

void loop(){

    updateFireAlarm();
    updateParking();

    bool fireNow = isFireDetected();

    if (fireNow){
        
        openAllGate();
        showFireAlarm();
        updateLCD();
        delay(2000);
    } else{
        
        if (wasFireDetected){
            closeAllGate();
        }

        updateEntrance(isParkingFull());
        updateExit();
        if (isParkingFull()){
            showParkingFull();
        }
    }

    wasFireDetected = fireNow;
    updateLCD();
}