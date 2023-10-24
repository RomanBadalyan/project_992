#include "RBDdimmer.h"
#include <GyverNTC.h>
#include <LiquidCrystal.h>
// #define ALL_DIMMERS 30
// int pwm;

dimmerLamp dimmer(5);
GyverNTC ntc (A4, 10000, 3950, 25, 10000); // Параметры и вход первого термистора
int x;
int y;
constexpr uint8_t PIN_RS = 41;  // 45
constexpr uint8_t PIN_EN = 39;  // 43
constexpr uint8_t PIN_DB4 = 37; // 53 
constexpr uint8_t PIN_DB5 = 35; // 51
constexpr uint8_t PIN_DB6 = 33; // 49
constexpr uint8_t PIN_DB7 = 31; // 47
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);
  lcd.begin(16, 2);
} 

void loop (){
x = 30;
y = 1.14*x + 68.8;
  dimmer.setPower(10);
          static uint32_t timer = millis();
          if (millis() - timer >= 1000) {
            timer = millis();
            lcd.setCursor(1, 0);
            lcd.println(ntc.getTempAverage()); 
          }

}
