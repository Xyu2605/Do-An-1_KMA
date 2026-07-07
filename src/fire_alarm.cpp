#include"config.h"
#include "fire_alarm.h"
#include <Arduino.h>

static bool fireDetected = false;

void initFireAlarm(){

    pinMode(FIRE_SENSOR, INPUT);
}

void updateFireAlarm()
{
    fireDetected = (digitalRead(FIRE_SENSOR) == LOW);

    if (fireDetected)
    {
        tone(BUZZER, 1000);   
    }
    else
    {
        noTone(BUZZER);     
    }
}

bool isFireDetected(){
    return fireDetected;
}