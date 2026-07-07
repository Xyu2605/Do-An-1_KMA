#pragma once

enum GateEvent {
    GATE_NONE,
    GATE_OPENED,
    GATE_CLOSED
};

void initGate();

GateEvent updateEntrance(bool parkingFull);

GateEvent updateExit();

void openAllGate();

void closeAllGate();