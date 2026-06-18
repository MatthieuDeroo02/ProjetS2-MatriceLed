#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <Arduino.h>
#include <stdlib.h>
#include "Horloge.hpp"
#include "MatriceLed.hpp"
#include "RTC_Eeprom.hpp"

extern clock myClock;

#define START_X 16
#define START_Y 4
#define START_LENGTH 3
#define START_SENS DROITE //0: HAUT, 1 : GAUCHE, 2 : DROITE, 3 : BAS

#define FOOD_NUMBER 1

#define DEBUG_SNAKE 1
#define SERIAL_MONITOR_BAUD 9600

#define SNAKE_SPEED

#define MASTER_SCORE_ADDR 0x67
#define MASTER_ACS_ADDR 0x71

#define BP1 PD2
#define BP2 PD3

#define BP1 PD2
#define BP2 PD3

void BP_Init();
bool BP1_Appuyer();
bool BP2_Appuyer();

struct T_Pose {
    uint8_t x;
    uint8_t y;
};

class Food {
public:
    void NewFood(T_Pose position);

    bool GetState();
    void SetState(bool state);
    T_Pose GetPose();
private:
    T_Pose __position;
    bool __state = 0;
};

class Snake {
public:
    void Begin();

    void Avancer();

    enum T_Direction {RIGHT, UP, LEFT, DOWN};
    void ChangeDirection(T_Direction turn);

    T_Pose* GetSnake();
    uint32_t GetSnakeSize();
    bool GetAvailableToTurn();
    bool GetTouchWall();
    bool GetTouchHimself();
    bool EatFood(Food *food);
    
    bool __touch_wall;
    bool __touch_himself;

private:
    bool __available_to_turn;

    uint32_t __SnakeSize = START_LENGTH;
    T_Pose __Snake[256];

    T_Direction __Snake_direction;
};

class SnakeGame {
public:
    void GameStart();
    bool UpdateGame();
    void EndGame();
    void CloseGame();

private:
    Snake mySnake;
    Food food1;
    Food food2;
    Food food3;
    Food food4;
    Food food5;

    void GenerateWindow();
    void ClearWindow();
    void SetLedWindow(uint8_t x, uint8_t y, bool state);

    uint8_t _uint32ToStr(uint32_t val, char* buf);

    T_Pose GenerateRandomPose();
    bool PositionIsFull(T_Pose position);

    friend void GenerateBufferLed();

    static bool __Snake_running;
    uint8_t __window[32];
    bool __is_dirty; //window need to be recalculated

    uint8_t __food_free;


    RTC_memoire myMemoire;
    uint32_t __master_score;
    uint8_t __master_acs;
    bool __rtc_memory_error;
    unsigned long __SnakeStart;
};

extern SnakeGame mySnakeGame;

#endif