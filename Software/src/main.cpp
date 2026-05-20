#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"

void setup() {
  myMatrice.begin();
  //myMatrice.AllOn();
  myMatrice.Clear();

  myMatrice.Print("hello\0", 2);

  myClock.Begin();
}

void loop() {
  myClock.Updates_Heures();
  myClock.Updates_Dates();
}
