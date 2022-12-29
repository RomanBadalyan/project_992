#include <GyverNTC.h> // Реализация уравнения Стейнхарта
/* 
Тестирование производилось на Arduino IDE 1.6.12
Дата тестирования 06.12.2016г.
*/ 
#include <LiquidCrystal.h>                // Подключяем библиотеку
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );    // Указываем порты 

GyverNTC ntc1 (A5, 10000, 3950, 25, 10000); // Параметры и вход первого термистора
byte simvol[8] = {B11100,B10100,B11100,B00000,B00000,B00000,B00000,B00000,}; // Символ градуса

const int dirPin1 = 13;
const int stepPin1 = 12;
const int MS1 = A2;
const int MS2 = A3;
const int MS3 = A4;
const int stepsPerRevolution1 = 1; 

//int pins_steps[]={11, 10, 3};  
//int steps[5][3]={
//  {0,0,0}, // 1
//  {1,0,0}, // 1/2
//  {0,1,0}, // 1/4
//  {1,1,0}, // 1/8
//  {1,1,1} // 1/16
//};
 
void setup()

{
  lcd.begin(16, 2);                       // Инициализируем LCD 16x2  
  lcd.setCursor(0,0);                     // Установить курсор на первую строку  
  lcd.print("Choose plastic");            // Вывести текст
  Serial.begin(9600);                     // Включаем последовательный порт
  
  // Объявить контакты как выходы
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
}

int z = 1;

void loop() {

if (z==1)
{
  // Установка направления вращения двигателя по часовой стрелке.
  digitalWrite(dirPin1, LOW);
  // Медленное вращение двигателя
    for(int z = 0; z < stepsPerRevolution1; z++)
    {
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(1000);
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(1000);
    }
  z = 1;
}

int x;                                    // Создаем переменную x
x = analogRead (1);                       // Задаем номер порта с которого производим считывание 
lcd.setCursor(0,0);                       // Установить курсор на вторую строку 
if (x < 100) {                            // Если x меньше 100 перейти на следующею строr
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, HIGH);                     
  lcd.print("Choosen plastic"); 
  lcd.setCursor(0,1);
  lcd.print ("PLA");                      // Вывести текст 
  lcd.setCursor(6,1);
  lcd.print(ntc1.getTempAverage());
  Serial.print("Value A0 ‘Right’ is  :"); // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 200) {                     // Если х меньше 200 перейти на следующию строку
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW); 
  lcd.print("Choosen plastic");
  lcd.setCursor(0,1); 
  lcd.print ("ABS");                      // Вывести текст 
  lcd.setCursor(6,1);
  lcd.print(ntc1.getTempAverage());
  Serial.print("Value A0 ‘Right’ is  :"); // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 400){                      // Если х меньше 400 перейти на следующию строку
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH); 
  lcd.print("Choosen plastic"); 
  lcd.setCursor(0,1);
  lcd.print ("PVA");                      // Вывести текст 
  lcd.setCursor(6,1);
  lcd.print(ntc1.getTempAverage());
  Serial.print("Value A0 ‘Right’ is  :"); // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 600){                      // Если х меньше 600 перейти на следующию строку
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  lcd.print("Choosen plastic"); 
  lcd.setCursor(0,1);
  lcd.print ("PPR");                      // Вывести текст 
  lcd.setCursor(6,1);
  lcd.print(ntc1.getTempAverage());
  Serial.print("Value A0 ‘Right’ is  :"); // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
}
