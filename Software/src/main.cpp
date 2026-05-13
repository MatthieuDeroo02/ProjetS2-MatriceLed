#include <Arduino.h>
#include "MatriceLed.hpp"

void setup() {
  DDRD = (1<<PD5) | (1<<PD4);
  Matrice.begin();
}

void loop() {
}
