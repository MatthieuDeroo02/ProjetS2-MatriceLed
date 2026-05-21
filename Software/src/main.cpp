#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"

void setup() {
  myMatrice.begin();
  //myMatrice.AllOn();
  myMatrice.Clear();

  Serial.begin(9600);

  //myClock.Begin();
  //myClock.Init_Heures();
}

void loop() {
    static int8_t index = 32;
    static unsigned long timer = 0;

    if ((myMatrice.millis() - timer) >= 80) { // >= au lieu de 
        myMatrice.Clear();
        myMatrice.Print("Seynod Neigeos\0", index);
        index--;
        timer = myMatrice.millis();
        if (index < -89) index = 32;
    }
}
