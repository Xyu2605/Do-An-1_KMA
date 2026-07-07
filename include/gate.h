#pragma once
#include <Servo.h>
#include <Arduino.h>

void initGate();

void updateEntrance(bool parkingFull);

void updateExit();

void openAllGate();

void closeAllGate();

void openGate(Servo &gate);
void closeGate(Servo &gate);