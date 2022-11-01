/* 
Тестирование производилось на Arduino IDE 1.6.12
Дата тестирования 06.12.2016г.
*/ 

#include <LiquidCrystal.h>                // Подключяем библиотеку
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );    // Указываем порты 

const int dirPin1 = 13;
const int stepPin1 = 12;
const int MS1 = 11;
const int MS2 = 10;
const int MS3 = A0;
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
  lcd.print("LCD1");                      // Вывести текст
//  lcd.setCursor(0,1);                     // Установить курсор на вторую строку
//  lcd.print("www.robotchip.ru");          // Вывести текст
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

if (z==1){
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

  int x;                                  // Создаем переменную x
  x = analogRead (1);                     // Задаем номер порта с которого производим считывание 
  lcd.setCursor(0,1);                     // Установить курсор на вторую строку 
  if (x < 100) {                          // Если x меньше 100 перейти на следующею строк
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(A0, HIGH);
  lcd.print ("Right ");                   // Вывести текст 
  Serial.print("Value A0 ‘Right’ is  :"); // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 200) {                     // Если х меньше 200 перейти на следующию строку
  digitalWrite(A0, LOW);
  lcd.print ("Up    ");                   // Вывести текст 
  Serial.print("Value A0 ‘UP’ is  :");    // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 400){                      // Если х меньше 400 перейти на следующию строку
  lcd.print ("Down  ");                   // Вывести текст
  Serial.print("Value A0 ‘Down’ is  :");  // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 600){                      // Если х меньше 600 перейти на следующию строку
  lcd.print ("Left  ");                   // Вывести текст
  Serial.print("Value A0 ‘Left’ is  :");  // Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
  else if (x < 800){                      // Если х меньше 800 перейти на следующию строку
  lcd.print ("Select");                   // Вывести текст
  Serial.print("Value A0 ‘Select’ is  :");// Вывести текст
  Serial.println(x,DEC);                  // Вывести значение переменной x
}
}
