#include "lcd_display.h"
#include "parking.h"
#include "config.h"
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

enum DisplayState{

    DISPLAY_DEFAULT,
    DISPLAY_WELCOME,
    DISPLAY_FULL,
    DISPLAY_PARK_SUCCESS,
    DISPLAY_GOODBYE,
    DISPLAY_FIRE
};

static DisplayState currentState;
static DisplayState lastState = DISPLAY_DEFAULT;
static unsigned long displayStartTime = 0;
static uint8_t currentSlot = 0;

const unsigned long DISPLAY_TIME = 2000;

void changeDisplay(DisplayState state)
{
    currentState = state;
    displayStartTime = millis();
}

void updateLCD(){

    // Sau 2 giây quay về màn hình mặc định
    if (currentState != DISPLAY_DEFAULT)
    {
        if (millis() - displayStartTime >= DISPLAY_TIME)
        {
            currentState = DISPLAY_DEFAULT;
        }
    }

    // Chỉ xóa LCD khi trạng thái thay đổi
    if (lastState != currentState)
    {
        lcd.clear();
        lastState = currentState;
    }

    switch(currentState) {

        case DISPLAY_DEFAULT:

            lcd.setCursor(0, 0);
            lcd.print("S1:");
            lcd.print(isSlotOccupied(0) ? "X" : "O");

            lcd.print(" S2:");
            lcd.print(isSlotOccupied(1) ? "X" : "0");

            lcd.setCursor(0, 1);
            lcd.print("S3:");
            lcd.print(isSlotOccupied(2) ? "X" : "0");

            lcd.print(" S4:");
            lcd.print(isSlotOccupied(3) ? "X" : "0");

            break;

        case DISPLAY_WELCOME:

            lcd.setCursor(0,0);
            lcd.print("Welcome!");
            
            lcd.setCursor(0,1);
            lcd.print("Free: | ");
            for(int i=0; i < MAX_SLOT; i++){
                if(!isSlotOccupied(i)){
                    lcd.print("S");
                    lcd.print(i+1);
                    lcd.print(" | ");
                }
            }

            break;

        case DISPLAY_FULL:

            lcd.setCursor(0,0);
            lcd.print("Parking full");

            break;

        case DISPLAY_PARK_SUCCESS:

            lcd.setCursor(0,0);
            lcd.print("Park Success");

            lcd.setCursor(0,1);
            lcd.print("Slot: S");
            lcd.print(currentSlot);

            break;

        case DISPLAY_GOODBYE:

            lcd.setCursor(2,0);
            lcd.print("Good Bye!");

            lcd.setCursor(1,1);
            lcd.print("See You Again");

            break;
            
        case DISPLAY_FIRE:

            lcd.setCursor(0,0);
            lcd.print(" FIRE ALARM! ");

            lcd.setCursor(0,1);
            lcd.print(" Exit Now!! ");

            break;
    }
}

void initLCD(){

    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Bao cao do an 1");
    lcd.setCursor(0,1);
    lcd.print("Hoc vien KTMM");
    delay(2000);

    lcd.clear();
}

void showDefaultScreen(){
    changeDisplay(DISPLAY_DEFAULT);
}

void showWelcome(){
    changeDisplay(DISPLAY_WELCOME);
}

void showParkingFull(){
    changeDisplay(DISPLAY_FULL);
}


void showParkSuccess(uint8_t slot)
{
    currentSlot = slot;
    changeDisplay(DISPLAY_PARK_SUCCESS);
}

void showGoodBye(){
    changeDisplay(DISPLAY_GOODBYE);
}

void showFireAlarm(){
    changeDisplay(DISPLAY_FIRE);
}