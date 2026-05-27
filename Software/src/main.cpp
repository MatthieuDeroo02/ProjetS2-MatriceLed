#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"
#include "SnakeLed.hpp"

//clock myClock;

void setup() {
  //myClock.Begin();
  myMatrice.begin();
  myMatrice.Clear();

  mySnakeGame.GameStart();
  
  //myMatrice.AllOn();
}

void loop() {
  mySnakeGame.UpdateGame();
}
