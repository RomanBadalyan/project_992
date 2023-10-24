#include <AccelStepper.h>
#define motorInterfaceType 1 
const int dirPin1 = 6;
const int stepPin1 = 7;
const int stepsPerRevolution1 = 1; 
AccelStepper myStepper1(motorInterfaceType, stepPin1, dirPin1);

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  myStepper1.setMaxSpeed(1000);
  myStepper1.setAcceleration(200);
  myStepper1.setSpeed(200);
  myStepper1.moveTo(10000000);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (myStepper1.distanceToGo() == 0) 
      {
        myStepper1.moveTo(myStepper1.currentPosition());
      }
  // Передвинуть на 1 шаг
    myStepper1.run();
}
