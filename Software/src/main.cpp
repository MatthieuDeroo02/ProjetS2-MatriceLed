#include <Arduino.h>
#include "SnakeLed.hpp"

clock myClock;


void setup() {
  /*Serial.begin(9600);
  Wire.begin();
  
  Serial.println("Scan I2C...");
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Appareil trouvé à 0x");
      Serial.println(addr, HEX);
    }
  }*/

  Serial.begin(9600);
  myClock.Begin();
  myMatrice.begin();


  mySnakeGame.GameStart();
  while(mySnakeGame.UpdateGame()) {};
  mySnakeGame.EndGame();
}

void loop() {
}
