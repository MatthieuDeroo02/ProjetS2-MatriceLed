#include <Arduino.h>
#include "MatriceLed.hpp"

MatriceLed enfer;

void setup() {
  enfer.begin();
}

void loop() {
  enfer.SetLed(x, y, state);
  enfer.Show();

}
