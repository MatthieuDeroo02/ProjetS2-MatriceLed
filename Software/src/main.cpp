#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"

void setup() {
  myMatrice.begin();
  myMatrice.AllOn();
  myMatrice.Clear();

  myMatrice.Print('H', 0);
  myMatrice.Print('E', 6);
  myMatrice.Print('L', 12);
  myMatrice.Print('L', 18);
  myMatrice.Print('O', 24);
}

void loop() {
  
}
