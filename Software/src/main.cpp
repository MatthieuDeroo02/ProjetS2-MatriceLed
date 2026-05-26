#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"

//clock myClock;

void setup() {
  //myClock.Begin();
  myMatrice.begin();
  myMatrice.Clear();
  //myMatrice.AllOn();
}

void loop() {
  myClock.PrintTimeOnMatrice();
}
