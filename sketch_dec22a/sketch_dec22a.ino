#include <EncButton.h>

#include <LiquidCrystal.h>
#include <GyverEncoder.h>

#define CLK 4
#define DT 3
#define SW 2

constexpr uint8_t PIN_RS = 45;
constexpr uint8_t PIN_EN = 43;
constexpr uint8_t PIN_DB4 = 53;  
constexpr uint8_t PIN_DB5 = 51;
constexpr uint8_t PIN_DB6 = 49;
constexpr uint8_t PIN_DB7 = 47;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

Encoder enc1(CLK, DT, SW);
int val = 0;

void setup() {
  Serial.begin(9600);
  enc1.setType(TYPE1);    // тип энкодера TYPE1 одношаговый, TYPE2 двухшаговый. Если ваш энкодер работает странно, смените тип
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("PLA");
  lcd.setCursor(1, 1);
  lcd.print("ABS");
}
void loop() {
  // обязательная функция отработки. Должна постоянно опрашиваться
  enc1.tick();
    if (enc1.isTurn()) {
    if (enc1.isRight()) val = val + 5;  // если был поворот направо, увеличиваем на 1
    if (enc1.isLeft()) val = val - 5;// если был поворот налево, уменьшаем на 1
    Serial.println(val);
  }  
}
