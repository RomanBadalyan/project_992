// параметры 1 шагового двигателя
const int dirPin1 = 2;
const int stepPin1 = 5;
const int stepsPerRevolution1 = 1; 

void setup() {
  // Объявить контакты как выходы
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
}

void loop() {
  digitalWrite(dirPin1, LOW);
  for(int i = 0; i < stepsPerRevolution1; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(1000);
  }
}
