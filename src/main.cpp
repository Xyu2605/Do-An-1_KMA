#include <Arduino.h>
#include "config.h"
#include "parking.h"
#include "fire_alarm.h"
#include "parking.h"
#include "lcd_display.h"
#include "gate.h"

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

    if (isFireDetected()){
        openAllGate();
        showFireAlarm();
    }
    else {
        updateEntrance(isParkingFull());
        updateExit();

        if (isParkingFull()){
            showParkingFull();
        }
        else if (getEnteredSlot() != -1){
            showWelcome();
        }
        else if (getExitedSlot() != -1){
            showGoodBye();
        }
    }

    updateLCD();
}