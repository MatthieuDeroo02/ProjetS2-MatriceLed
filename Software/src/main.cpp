#include <Arduino.h>
#include "MatriceLed.hpp"

MatriceLed enfer;

void setup() {
  enfer.begin();
}

void loop() {
  enfer.SetLed(MATRICE_SIZE_X, MATRICE_SIZE_Y, STATE);
  enfer.Show();

}
