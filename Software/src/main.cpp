#include <Arduino.h>
#include "SnakeLed.hpp"

clock myClock;

typedef enum T_State {TIME, SNAKE_START, SNAKE_IN_GAME, BUS};

typedef struct T_Input {
  bool bp1;
  bool tmp_bp1;
  bool bp2;
  bool tmp_bp2;
  bool snake_lose;
  T_State laste_state;
};

void ReadInput();
void UpdateState();
void UpdateOutput();

T_State state;
T_Input input;


void setup() {

  Serial.begin(9600);
  myClock.Begin();
  myMatrice.begin();
  BP_Init();

  input.laste_state = TIME;
  state = TIME;
}

void loop() {
}

void ReadInput() {
  input.tmp_bp1 = input.bp1;
  input.bp1 = BP1_Appuyer();
  input.tmp_bp2 = input.bp2;
  input.bp2 = BP2_Appuyer();

  input.laste_state = state;
}

void UpdateState() {
  switch (state) {
    case TIME:
      if ((input.tmp_bp1 == true) && (input.bp1 == false)) state = SNAKE_START;
      break;
    case SNAKE_START:
      if ((input.tmp_bp1 == true) && (input.bp1 == false)) state = BUS;
      if ((input.tmp_bp2 == true) && (input.bp2 == false)) state = SNAKE_IN_GAME;
      break;
    case BUS:
      if ((input.tmp_bp1 == true) && (input.bp1 == false)) state = TIME;
      break;
  }
}

void UpdateOutput() {
  switch (state) {
    case TIME:
      myClock.PrintTimeOnMatrice();
      break;

    case SNAKE_START:
      if (input.laste_state != SNAKE_START) mySnakeGame.GameStart();
      break;

    case SNAKE_IN_GAME:
      if (!mySnakeGame.UpdateGame()) {
        mySnakeGame.EndGame();
        state = SNAKE_START;
      }
      break;

    case BUS:
      if (input.laste_state != BUS) {
        myMatrice.Clear();
        myMatrice.Print('4', 1);
        for (int i=0; i<8; i++) {
          myMatrice.SetLed(7, i, ON);
        }
      }
      
      static int8_t index = 32;
      static unsigned long timer = 0;

      if ((newMillis() - timer) >= 100) { // >= au lieu de 
        myMatrice.ClearZone(8, MATRICE_SIZE_X-1);
        myMatrice.Print("Seynod Neigeos\0", index, 8, MATRICE_SIZE_X-1);
        index--;
        timer = newMillis();
        if (index < -79) index = 32;
      }
      break;
  }
}
