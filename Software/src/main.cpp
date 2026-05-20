#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"

void setup() {
  myMatrice.begin();
  //myMatrice.AllOn();
  myMatrice.Clear();

  myMatrice.Print("ARRET\0", 0);

  //myClock.Begin();
}

void loop() {
  //myClock.Updates_Heures();
  //myClock.Updates_Dates();
}
