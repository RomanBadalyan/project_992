const int dirPin1 = 8;
const int stepPin1 = 9;
const int stepsPerRevolution1 = 1; 
boolean buttonWasUp = true;
boolean ledEnabled = false;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT); }

int y = 1;
void loop() {
 // узнаем, отпущена ли кнопка сейчас
   boolean buttonIsUp = digitalRead(2);
   // если кнопка была отпущена и не отпущена сейчас
   if (buttonWasUp && !buttonIsUp) {
      // исключаем дребезг контактов тактовой кнопки
      delay(10);
    // и считываем сигнал с кнопки снова
    buttonIsUp = digitalRead(2);
      // если кнопка нажата, то переворачиваем сигнал светодиода
      if (!buttonIsUp) {
         ledEnabled = !ledEnabled;
         digitalWrite(3, ledEnabled);
            Serial.println(ledEnabled);
      }
   }
   // запоминаем состояние кнопки для новой итерации
   buttonWasUp = buttonIsUp;

  if (y == 1 && ledEnabled == 1) {
    digitalWrite(dirPin1, HIGH);
      for(int i = 0; i < stepsPerRevolution1; i++) {
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(1000);
      }
    y = 1;
  }
}
