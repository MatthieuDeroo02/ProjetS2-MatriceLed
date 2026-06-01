#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"
#include "SnakeLed.hpp"
#include "RTC_Eeprom.hpp"

clock myClock;
RTC_memoire myMemoire;

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
  myMemoire.Begin(RTC_EEPROM_I2C_ADDR);
  myMemoire.WriteByte(0X0, 26);

  bool error;
  Serial.println(myMemoire.ReadByte(0x0, &error));
  Serial.print("ERROR: ");
  Serial.print(error);

  /*
  myMatrice.Clear();

  mySnakeGame.GameStart();
  while(mySnakeGame.UpdateGame()) {};
  mySnakeGame.EndGame();
  
  
  //myMatrice.AllOn();*/
}

void loop() {
}
