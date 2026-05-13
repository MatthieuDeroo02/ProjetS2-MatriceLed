#include <Arduino.h>
#include "MatriceLed.hpp"

MatriceLed matrice;

void setup() {
  DDRD = (1<<PD5) | (1<<PD4);
  matrice.begin();
}

void loop() {
}
