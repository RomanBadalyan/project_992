#include <AccelStepper.h>
const int dirPin = 5;
const int stepPin = 6;
//const int stepsPerRevolution1 = 1000;
#define motorInterfaceType 1
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  myStepper.setMaxSpeed(600);
  myStepper.setAcceleration(200);
  myStepper.setSpeed(200);
  myStepper.moveTo(10000000);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT); 
}
void loop() {
  if (myStepper.distanceToGo() == 0) 
  {
    myStepper.moveTo(myStepper.currentPosition());
  }
  // Передвинуть на 1 шаг
  myStepper.run();
//digitalWrite(dirPin1, LOW);
//  for(int x = 0; x < stepsPerRevolution1; x++)
//  {
//    digitalWrite(stepPin1, HIGH);
//    delayMicroseconds(1000);
//    digitalWrite(stepPin1, LOW);
//    delayMicroseconds(1000);
//  }
}
