#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"
#include "SnakeLed.hpp"

void setup() {
  myMatrice.begin();
  //myMatrice.AllOn();
  myMatrice.Clear();

  myMatrice.Print('4', 0);
  for (int i=0; i<8; i++) {
    myMatrice.SetLed(6, i, ON);
  }

  //Serial.begin(9600);

  //myClock.Begin();
  //myClock.Init_Heures();
}

void loop() {
    static int8_t index = 32;
    static unsigned long timer = 0;

    if ((myMatrice.millis() - timer) >= 80) { // >= au lieu de 
        myMatrice.ClearZone(7, MATRICE_SIZE_X-1);
        myMatrice.Print("Seynod Neigeos\0", index, 7, MATRICE_SIZE_X-1);
        index--;
        timer = myMatrice.millis();
        if (index < -83) index = 32;
    }
}
