
 // Подключаем библиотеку AccelStepper
#include <AccelStepper.h>
// Устанавливаем выводы
const int dirPin = 2;
const int stepPin = 5;

// Определение тип интерфейса двигателя
#define motorInterfaceType 1
// Создаем экземпляр
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);
void setup() {
  // Устанавливаем максимальную скорость, коэффициент ускорения,
  // начальную скорость и целевую позицию
  myStepper.setMaxSpeed(800);
  myStepper.setAcceleration(50);
  myStepper.setSpeed(100);
  myStepper.moveTo(10000000);
  
}
void loop() {

  // Изменение направления вращения, когда двигатель достигнет заданного положения
  if (myStepper.distanceToGo() == 0) 
  {
    myStepper.moveTo(myStepper.currentPosition());
  }
  // Передвинуть на 1 шаг
  myStepper.run();
}
