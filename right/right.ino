#include <LiquidCrystal.h>
#include <GyverEncoder.h>
#include <GyverNTC.h>

#define CLK 4
#define DT 3
#define SW 2 

constexpr uint8_t PIN_RS = 45;  // 45
constexpr uint8_t PIN_EN = 43;  // 43
constexpr uint8_t PIN_DB4 = 53; // 53 
constexpr uint8_t PIN_DB5 = 51; // 51
constexpr uint8_t PIN_DB6 = 49; // 49
constexpr uint8_t PIN_DB7 = 47; // 47

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
GyverNTC ntc (A4, 10000, 3950, 25, 10000); // Параметры и вход первого термистора
Encoder enc1(CLK, DT, SW); 

int8_t arrowPos = 0; 
boolean check = false;
const int dirPin1 = 5;
const int stepPin1 = 6;
const int stepsPerRevolution1 = 1; 

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT); 
  
  Serial.begin(9600);
  enc1.setType(TYPE1);
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("ReCoil  System");
  lcd.setCursor(0, 1);
  lcd.print("--turn  button--");
}

int y = 0;

void GUI() {
  digitalWrite(A0, LOW); 
  digitalWrite(A1, LOW); 
  digitalWrite(A2, LOW); 
  digitalWrite(A3, LOW); 
  lcd.setCursor(1, 0); lcd.print("PLA"); 
  lcd.setCursor(9, 0); lcd.print("ABS"); 
  lcd.setCursor(1, 1); lcd.print("PET"); 
  lcd.setCursor(9, 1); lcd.print("PP+"); 
  // выводим стрелку
  switch (arrowPos) {
    case 0: lcd.setCursor(0, 0);
      break;
    case 1: lcd.setCursor(8, 0);
      break;
    case 2: lcd.setCursor(0, 1);
      break;
    case 3: lcd.setCursor(8, 1);
      break;
  }
  Serial.println(arrowPos);
  lcd.write(">");   // вывести стрелку
}

void plastic() {
  switch (arrowPos) {
    
    case 0: if (enc1.isClick()) {
      y = 1;
      digitalWrite(A0, HIGH); 
      digitalWrite(A1, LOW); 
      digitalWrite(A2, LOW); 
      digitalWrite(A3, LOW); 
      lcd.clear(); 
      lcd.print("Your choice PLA"); 
      lcd.setCursor(0, 1);
      lcd.print("Temp:"); 
      check = true; }
        break;
          
    case 1: if (enc1.isClick()) {
      y = 1;
      digitalWrite(A0, LOW); 
      digitalWrite(A1, HIGH); 
      digitalWrite(A2, LOW); 
      digitalWrite(A3, LOW); 
      lcd.clear(); 
      lcd.print("Your choice ABS"); 
      lcd.setCursor(0, 1);
      lcd.print("Temp:"); 
      check = true; }
        break;
          
    case 2: if (enc1.isClick()) {
      y = 1;
      digitalWrite(A0, LOW); 
      digitalWrite(A1, LOW); 
      digitalWrite(A2, HIGH); 
      digitalWrite(A3, LOW); 
      lcd.clear(); 
      lcd.print("Your choice PET"); 
      lcd.setCursor(0, 1);
      lcd.print("Temp:"); 
      check = true; }
        break;
          
    case 3: if (enc1.isClick()) {
      y = 1;
      digitalWrite(A0, LOW); 
      digitalWrite(A1, LOW); 
      digitalWrite(A2, LOW); 
      digitalWrite(A3, HIGH); 
      lcd.clear(); 
      lcd.print("Your choice PP+"); 
      lcd.setCursor(0, 1);
      lcd.print("Temp:"); 
      check = true; }
        break; 
  }
}

void loop() {
  if (y == 1) {
    digitalWrite(dirPin1, HIGH);
      for(int i = 0; i < stepsPerRevolution1; i++) {
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(1000);
      }
    y = 1;
  }
  Serial.println(check);
  enc1.tick();
    if (enc1.isTurn()) { // при любом повороте
      y = 0;
      check = false;
        if (enc1.isRight() ) {
          arrowPos++;  lcd.clear(); 
        if (arrowPos > 3) arrowPos = 0; // ограничиваем позицию курсора
        }
        if (enc1.isLeft() ) {
          arrowPos--;  lcd.clear();
        if (arrowPos < 0) arrowPos = 3; // ограничиваем позицию курсора
        }
    GUI();
    } 
    else {
      if (check) {
        static uint32_t timer = millis();
          if (millis() - timer >= 1000) {
            timer = millis();
            lcd.setCursor(6, 1);
            lcd.print(ntc.getTempAverage()); 
          }
      }
    }
  plastic();
}
