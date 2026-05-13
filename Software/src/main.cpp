#include <Arduino.h>
#include "MatriceLed.hpp"

MatriceLed matrice;

void setup() {
  DDRD = (1<<5);
  matrice.begin();
}

void loop() {

}
