
#include <GyverNTC.h>

GyverNTC ntc (A0, 10000, 3950, 25, 10000); // Параметры и вход первого термистора

void setup() {
  Serial.begin(9600);
}

void loop() {
    static uint32_t timer = millis();
  if (millis() - timer >= 1000) {
    timer = millis();
    Serial.println(ntc.getTempAverage());
  }
}
