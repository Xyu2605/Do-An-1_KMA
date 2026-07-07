#include "parking.h"
#include "config.h"

#include <Arduino.h>

static bool slotState[MAX_SLOT];
static bool lastSlotState[MAX_SLOT];
static int carCount = 0;

static const uint8_t slot[MAX_SLOT] ={
    SLOT1,
    SLOT2,
    SLOT3,
    SLOT4
};

void initParking() {

    for (int i = 0; i < MAX_SLOT; i++){
        pinMode(slot[i], INPUT);
    }
}

void updateParking() {

    carCount = 0;
    for (int i = 0; i < MAX_SLOT; i++)
    {
        lastSlotState[i] = slotState[i];
        slotState[i] = (digitalRead(slot[i]) == LOW);
        if (slotState[i]){
            carCount++;
        }
    }
}

bool isParkingFull() {
    return carCount >= MAX_SLOT;
}

bool isSlotOccupied(uint8_t slot) {
    if (slot >= MAX_SLOT)
        return false;

    return slotState[slot];
}