#include"config.h"
#include "fire_alarm.h"
#include <Arduino.h>

static bool fireDetected = false;

void initFireAlarm(){

    pinMode(FIRE_SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);

    digitalWrite(BUZZER, LOW);
}

void updateFireAlarm(){

    fireDetected = (digitalRead(FIRE_SENSOR) == LOW);

    if (fireDetected){
        digitalWrite(BUZZER, HIGH);
    } else{
        digitalWrite(BUZZER, LOW);
    }
}

bool isFireDetected(){
    return fireDetected;
}