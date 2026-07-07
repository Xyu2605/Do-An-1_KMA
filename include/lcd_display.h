#pragma once
#include <stdint.h>

void initLCD();

void showDefaultScreen();

void showWelcome();

void showParkingFull();

void showParkSuccess(uint8_t slot);

void showGoodBye();

void showFireAlarm();

void updateLCD();