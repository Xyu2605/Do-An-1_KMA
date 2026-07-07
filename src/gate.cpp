#include "gate.h"
#include "config.h"
#include "lcd_display.h"
#include <Arduino.h>
#include <Servo.h>

Servo gateIn;
Servo gateOut;

void initGate(){

    pinMode(TRIG_IN, OUTPUT);
    pinMode(ECHO_IN, INPUT);

    pinMode(TRIG_OUT, OUTPUT);
    pinMode(ECHO_OUT, INPUT);

    gateIn.attach(SERVO_IN);
    gateOut.attach(SERVO_OUT);

    closeAllGate();
}

float getDistance(int trigPin, int echoPin) {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
        return 999;

    return duration * 0.0343 / 2.0;
}

void updateEntrance(bool parkingFull) {

    float d = getDistance(TRIG_IN, ECHO_IN);

    if (d < OPEN_DISTANCE && !parkingFull){
        Serial.println("Open Entrance");
        
        for (int pos = GATE_ANGLE; pos >= 0; pos--){
            gateIn.write(pos);
            delay(10);
        }
        
        showWelcome();
        updateLCD(); 
        delay(3000);

      // Chờ xe đi qua
        for (int pos = 0; pos <= GATE_ANGLE; pos++){
            gateIn.write(pos);
            delay(10);
        }
        Serial.println("Close Entrance");
    }
}


void updateExit(){

    float d = getDistance(TRIG_OUT, ECHO_OUT);

    if (d < OPEN_DISTANCE)
    {
        Serial.println("Open Exit");

        for( int pos=0; pos< GATE_ANGLE; pos++){
            gateOut.write(pos);
            delay(10);
        }

        delay(3000);

        for (int pos = GATE_ANGLE; pos >= 0; pos--) {
            gateOut.write(pos);
            delay(10);
        }
        showGoodBye();
        Serial.println("Close Exit");
    }
}

void openAllGate() {
    gateIn.write(0);
    gateOut.write(90);
}

void closeAllGate() {
    gateIn.write(GATE_ANGLE);
    gateOut.write(0);
}
