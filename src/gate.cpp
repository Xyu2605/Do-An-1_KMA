#include "gate.h"
#include "config.h"
#include <Arduino.h>
#include <Servo.h>

Servo gateIn;
Servo gateOut;

enum GateState{

    WAIT_CAR,
    GATE_OPEN,
};

GateState inState = WAIT_CAR;
GateState outState = WAIT_CAR;

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

GateEvent updateEntrance(bool parkingFull)
{
    float d = getDistance(TRIG_IN, ECHO_IN);

    switch (inState)
    {
        case WAIT_CAR:

            if (d < OPEN_DISTANCE && !parkingFull)
            {
                gateIn.write(GATE_OPEN_ANGLE);
                inState = GATE_OPEN;

                return GATE_OPENED;
            }

            break;

        case GATE_OPEN:

            if (d > CLOSE_DISTANCE)
            {
                gateIn.write(GATE_CLOSE_ANGLE);
                inState = WAIT_CAR;

                return GATE_CLOSED;
            }

            break;
    }

    return GATE_NONE;
}


GateEvent updateExit()
{
    float d = getDistance(TRIG_OUT, ECHO_OUT);

    switch (outState)
    {
        case WAIT_CAR:

            if (d < OPEN_DISTANCE)
            {
                gateOut.write(GATE_OPEN_ANGLE);
                outState = GATE_OPEN;

                return GATE_OPENED;
            }

            break;

        case GATE_OPEN:

            if (d > CLOSE_DISTANCE)
            {
                gateOut.write(GATE_CLOSE_ANGLE);
                outState = WAIT_CAR;

                return GATE_CLOSED;
            }

            break;
    }

    return GATE_NONE;
}

void openAllGate() {
    gateIn.write(GATE_OPEN_ANGLE);
    gateOut.write(GATE_OPEN_ANGLE);
}

void closeAllGate() {
    gateIn.write(GATE_CLOSE_ANGLE);
    gateOut.write(GATE_CLOSE_ANGLE);
}