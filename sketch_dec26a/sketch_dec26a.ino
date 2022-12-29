// пример с простым шахматным меню
// пины энкодера
#define CLK 4
#define DT 3
#define SW 2

#include <LiquidCrystal.h>
#include <GyverEncoder.h>
Encoder enc1(CLK, DT, SW);  // для работы c кнопкой

constexpr uint8_t PIN_RS = 45;
constexpr uint8_t PIN_EN = 43;
constexpr uint8_t PIN_DB4 = 53;  
constexpr uint8_t PIN_DB5 = 51;
constexpr uint8_t PIN_DB6 = 49;
constexpr uint8_t PIN_DB7 = 47;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

// переменные
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

int8_t arrowPos = 0;  // позиция стрелки

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT); 
  
  Serial.begin(9600);
  enc1.setType(TYPE1);
  lcd.begin(16, 2);
}

void printGUI() {
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

void loop() {
  enc1.tick();

  if (enc1.isTurn()) {  // при любом повороте
    lcd.clear();        // очищаем дисплей

    if (enc1.isLeft() ) {
      arrowPos++;  lcd.clear();
      if (arrowPos >= 4) arrowPos = 0;  // ограничиваем позицию курсора
    }
    if (enc1.isRight() ) {
      arrowPos--;  lcd.clear();
      if (arrowPos < 0) arrowPos = 3;  // ограничиваем позицию курсора
    }

    printGUI();
    
      switch (arrowPos)   {
        case 1: if (enc1.isClick()) {
        digitalWrite(A0, HIGH); digitalWrite(A1, LOW); digitalWrite(A2, LOW); digitalWrite(A3, LOW); lcd.clear(); lcd.setCursor(0, 0); lcd.print("Your choice PLA"); }
          break;
          
        case 2: if (enc1.isClick()) {
        digitalWrite(A0, LOW); digitalWrite(A1, HIGH); digitalWrite(A2, LOW); digitalWrite(A3, LOW); lcd.clear(); lcd.setCursor(0, 0); lcd.print("Your choice ABS"); }
          break;
          
        case 3: if (enc1.isClick()) {
        digitalWrite(A0, LOW); digitalWrite(A1, LOW); digitalWrite(A2, HIGH); digitalWrite(A3, LOW); lcd.clear(); lcd.setCursor(0, 0); lcd.print("Your choice PET"); }
          break;
          
        case 0: if (enc1.isClick()) {
        digitalWrite(A0, LOW); digitalWrite(A1, LOW); digitalWrite(A2, LOW); digitalWrite(A3, HIGH); lcd.clear(); lcd.setCursor(0, 0); lcd.print("Your choice PP+"); }
          break; 
    }   
  }
}
