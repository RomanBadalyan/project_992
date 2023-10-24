# include <Servo.h>

Servo servo1;
const int switchPin = 7;
const int pinX = A0;
const int pinY = A1;
const int ledPin = 13;

void setup() {
  servo1.attach(8);
  pinMode(ledPin, OUTPUT);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  digitalWrite(switchPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  freeMode();
}

void freeMode() {
//  servo1.write(0);
//  delay(1500);
//  servo1.write(180);
//  delay(1500);

  int ledState = digitalRead(switchPin);
  digitalWrite(ledPin, ledState);
  int X = analogRead(pinX);
  int Y = analogRead(pinY);
  Serial.print(X);
  Serial.print("\t");
  Serial.println(Y);
  delay(300);

  int yAngle = map(Y, 0, 1023, 0, 180);
  int xAngle = map(X, 0, 1023, 0, 180);

  servo1.write(yAngle);
}
