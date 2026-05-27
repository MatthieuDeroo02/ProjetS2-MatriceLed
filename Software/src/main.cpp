#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"
#include "SnakeLed.hpp"

//clock myClock;

void setup() {
  //myClock.Begin();
  myMatrice.begin();
  myMatrice.Clear();

  mySnake.InitSnake();
  
  //myMatrice.AllOn();
}

void loop() {
        mySnake.SnakeGame();
        mySnake.PrintSnake();
  //myClock.PrintTimeOnMatrice();
}
