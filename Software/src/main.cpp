#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"
#include "SnakeLed.hpp"

//clock myClock;

void setup() {
  Serial.begin(9600);
  //myClock.Begin();
  //myMatrice.begin();
  //myMatrice.Clear();

  //mySnakeGame.GameStart();
  
  //myMatrice.AllOn();
}

void loop() {
  //mySnakeGame.UpdateGame();

  Serial.print(BP1_Appuyer());
  Serial.print("  |  ");
  Serial.println(BP2_Appuyer());
}
