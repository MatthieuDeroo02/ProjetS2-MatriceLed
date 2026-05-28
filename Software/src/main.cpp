#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"
#include "SnakeLed.hpp"

//clock myClock;

void setup() {
  //Serial.begin(9600);
  //myClock.Begin();
  myMatrice.begin();
  myMatrice.Clear();

  mySnakeGame.GameStart();
  while(mySnakeGame.UpdateGame()) {};
  mySnakeGame.EndGame();
  
  //myMatrice.AllOn();
}

void loop() {
}
