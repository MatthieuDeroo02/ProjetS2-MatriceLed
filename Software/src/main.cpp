#include <Arduino.h>
#include "MatriceLed.hpp"

MatriceLed matrice(500, 50000);

void setup() {
  DDRD = (1<<5);
  matrice.begin();
}

void loop() {

}
