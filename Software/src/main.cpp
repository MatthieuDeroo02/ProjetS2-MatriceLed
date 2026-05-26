#include <Arduino.h>
#include "Horloge.hpp"

clock myClock;

void setup() {
  myClock.Begin(2026, 5, 26, 15, 15, 0);
}

void loop() {
  myClock.UpdateRTC();
  Serial.print(myClock.GetHour());
  Serial.print(":");
  if (myClock.GetMinute() < 10) Serial.print("0"); // zéro devant si < 10
  Serial.print(myClock.GetMinute());
  Serial.print(":");
  if (myClock.GetSecond() < 10) Serial.print("0");
  Serial.println(myClock.GetSecond());

  delay(1000);
}
