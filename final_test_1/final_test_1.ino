#include <LiquidCrystal.h>
#include <GyverEncoder.h>
#include <GyverNTC.h>
#include <AccelStepper.h>
#include "RBDdimmer.h"

#define CLK 4
#define DT 3
#define SW 1
#define motorInterfaceType 1  

constexpr uint8_t PIN_RS = 41;  // 45
constexpr uint8_t PIN_EN = 39;  // 43
constexpr uint8_t PIN_DB4 = 37; // 53 
constexpr uint8_t PIN_DB5 = 35; // 51
constexpr uint8_t PIN_DB6 = 33; // 49
constexpr uint8_t PIN_DB7 = 31; // 47

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
GyverNTC ntc (A4, 10000, 3950, 25, 10000); // Параметры и вход первого термистора
Encoder enc1(CLK, DT, SW); 
dimmerLamp dimmer(5);

int start_motor = 0;
int power;
int8_t set_mode_Pos = 0;
int8_t rotate_menu_Pos = 0;
int8_t heat_menu_Pos = 0;
boolean mode_menu = true;
boolean set_mode_menu = false;
boolean rotate_menu = false;
boolean heat_menu = false;
int temp_counter = 50;
//boolean check = false;
const int dirPin1 = 6; 
const int stepPin1 = 7;
const int stepsPerRevolution1 = 1; 
//const int dirPin2 = 8;
//const int stepPin2 = 10;
//const int stepsPerRevolution2 = 1; 
//boolean buttonWasUp = true;
//boolean ledEnabled = false;
AccelStepper myStepper1(motorInterfaceType, stepPin1, dirPin1);
//AccelStepper myStepper2(motorInterfaceType, stepPin2, dirPin2);

void setup() {
  dimmer.begin(NORMAL_MODE, ON);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
//  pinMode(43, OUTPUT);
//  pinMode(45, INPUT_PULLUP);
//  myStepper2.setMaxSpeed(1000);
//  myStepper2.setAcceleration(100);
//  myStepper2.setSpeed(100);
//  myStepper2.moveTo(-10000000);
//  pinMode(stepPin2, OUTPUT);
//  pinMode(dirPin2, OUTPUT);
  myStepper1.setMaxSpeed(1000);
  myStepper1.setAcceleration(200);
  myStepper1.setSpeed(200);
  myStepper1.moveTo(10000000);
  
//  pinMode(A0, OUTPUT);
//  pinMode(A1, OUTPUT);
//  pinMode(A2, OUTPUT);
//  pinMode(A3, OUTPUT); 
  
  Serial.begin(9600);
  enc1.setType(TYPE2);
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("ReCoil  System");
  lcd.setCursor(0, 1);
  lcd.print("--turn  button--"); 
}

void SET_MODE_MENU() {
  switch (set_mode_Pos) {
    case 1: if (enc1.isClick() ) {
      lcd.clear();
      lcd.setCursor(1, 0); lcd.print("hold to start"); 
      lcd.setCursor(1, 1); lcd.print("back");
      mode_menu = false;
      set_mode_menu = true;
      rotate_menu = true;
      Serial.println(rotate_menu_Pos);
    }
//    enc1.resetStates();
//    if (rotate_menu_Pos == 1 && enc1.isClick() ) { mode_menu = true; rotate_menu = false; }
    break;
    case 2: if (enc1.isClick() ) {
      lcd.clear();
      lcd.setCursor(1, 0); lcd.print("temp:"); 
      lcd.setCursor(1, 1); lcd.print("back");
      mode_menu = false;
      set_mode_menu = true;
      heat_menu = true;
    }
    break;
    case 0: if (enc1.isClick() ) {
      lcd.clear();
      lcd.setCursor(1, 0); lcd.print("PLA"); 
      lcd.setCursor(9, 0); lcd.print("Custom"); 
      lcd.setCursor(1, 1); lcd.print("ABS"); 
      lcd.setCursor(9, 1); lcd.print("back"); 
      mode_menu = false;
      set_mode_menu = true;
    }
    break;
  }
}

void ROTATE_MENU() {
  lcd.setCursor(1, 0); lcd.print("hold to start");  
  lcd.setCursor(1, 1); lcd.print("back");
  switch (rotate_menu_Pos) {
    case 0: lcd.setCursor(0, 0);
      break;
    case 1: lcd.setCursor(0, 1); 
      break;
  } 
  lcd.write(">");
}

void HEAT_MENU() {
  lcd.setCursor(1, 0); lcd.print("temp:");  
  lcd.setCursor(1, 1); lcd.print("back");
  switch (heat_menu_Pos) {
    case 0: lcd.setCursor(0, 0);
      break;
    case 1: lcd.setCursor(0, 1); 
      break;
  } 
  lcd.write(">");
}

void SET_MODE() {
  lcd.setCursor(1, 0); lcd.print("start"); 
  lcd.setCursor(1, 1); lcd.print("rotate");
  lcd.setCursor(9, 0); lcd.print("heat");  
  // выводим стрелку
    switch (set_mode_Pos) {
    case 0: lcd.setCursor(0, 0);
      break;
    case 1: lcd.setCursor(0, 1); 
      break;
    case 2: lcd.setCursor(8, 0);
      break;
    } 
  lcd.write(">");   // вывести стрелку
  Serial.println(set_mode_Pos);
}

void loop() {
  enc1.tick();
  enc1.isTurn();
  if ( rotate_menu && rotate_menu_Pos == 0 && enc1.isHold() ) {
//    lcd.setCursor(8, 0); lcd.print("active  ");
    if (myStepper1.distanceToGo() == 0) 
      {
        myStepper1.moveTo(myStepper1.currentPosition());
      }
  // Передвинуть на 1 шаг
    myStepper1.run();
    enc1.resetStates();
  }
  if ( heat_menu ) {
    dimmer.setPower(30);
    if ( heat_menu_Pos == 0 && enc1.isRightH() ) {
      temp_counter++; 
      lcd.setCursor(7, 0); 
      lcd.print(temp_counter); 
      lcd.setCursor(10, 0); 
      lcd.print("/");
        if (temp_counter >= 180) { temp_counter = 180; 
        }
    }
    if ( heat_menu_Pos == 0 && enc1.isLeftH() ) {
      temp_counter--; 
      lcd.setCursor(7, 0); 
      lcd.print(temp_counter); 
      lcd.setCursor(10, 0); 
      lcd.print("/"); 
        if (temp_counter <= 50) { temp_counter = 50; 
        }
    }
    power = 0.0001*pow(temp_counter, 3) - 0.0352*pow(temp_counter, 2) + 2.3819*temp_counter - 0.0227;
    static uint32_t timer = millis();
         if (millis() - timer >= 1000) {
          timer = millis();
          lcd.setCursor(11, 0);
          lcd.print(ntc.getTempAverage()); }
  }
  enc1.tick();
    if (enc1.isTurn() && mode_menu) { 
      // при любом повороте
      start_motor = 0;
        if (enc1.isRight() ) {
          set_mode_Pos++;  lcd.clear(); 
        if (set_mode_Pos > 2) set_mode_Pos = 0; // ограничиваем позицию курсора
        }
        if (enc1.isLeft() ) {
          set_mode_Pos--;  lcd.clear();
        if (set_mode_Pos < 0) set_mode_Pos = 2; // ограничиваем позицию курсора
        }
    SET_MODE();
    }
    else { if (set_mode_menu) {
        static uint32_t timer = millis();
          if (millis() - timer >= 1000) {
            timer = millis();
          }
    }
          SET_MODE_MENU();
    }
    enc1.resetStates();
    enc1.tick(); 
    if (enc1.isTurn() && rotate_menu) { 
      // при любом повороте
        if (enc1.isRight() ) {
          rotate_menu_Pos++;  lcd.clear(); 
        if (rotate_menu_Pos > 1) rotate_menu_Pos = 0; // ограничиваем позицию курсора
        }
        if (enc1.isLeft() ) {
          rotate_menu_Pos--;  lcd.clear();
        if (rotate_menu_Pos < 0) rotate_menu_Pos = 1; // ограничиваем позицию курсора
        }
      ROTATE_MENU();
    }
    enc1.resetStates();
    enc1.tick(); 
    if (enc1.isTurn() && heat_menu) { 
      // при любом повороте
        if (enc1.isRight() ) {
          heat_menu_Pos++;  lcd.clear(); 
        if (heat_menu_Pos > 1) heat_menu_Pos = 0; // ограничиваем позицию курсора
        }
        if (enc1.isLeft() ) {
          heat_menu_Pos--;  lcd.clear();
        if (heat_menu_Pos < 0) heat_menu_Pos = 1; // ограничиваем позицию курсора
        }
      HEAT_MENU();
    }
    if ( rotate_menu_Pos == 1 && enc1.isClick() ) { mode_menu = true; rotate_menu = false; }
    if ( heat_menu_Pos == 1 && enc1.isClick() ) { mode_menu = true; heat_menu = false; }
}
