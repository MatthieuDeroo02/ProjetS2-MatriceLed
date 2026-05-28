#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#include <Arduino.h>
#include <stdlib.h>
#include "Horloge.hpp"
#include "MatriceLed.hpp"

#define START_X 16
#define START_Y 4
#define START_LENGTH 3
#define START_SENS DROITE //0: HAUT, 1 : GAUCHE, 2 : DROITE, 3 : BAS

#define FOOD_NUMBER 1

#define DEBUG_SNAKE 1
#define SERIAL_MONITOR_BAUD 9600

#define SNAKE_SPEED

#define BP1 PD2
#define BP2 PD3

#define Masque_PD2 1<<2
#define Masque_PD3 1<<3

bool BP1_Appuyer();
bool BP2_Appuyer();

typedef struct T_Pose {
    uint8_t x;
    uint8_t y;
};

class Snake {
public:
    void Begin();

    void AddSize();

    void Avancer();

    typedef enum T_Turn {RIGHT, LEFT};
    void ChangeDirection(T_Turn turn);

    T_Pose* GetSnake();
    uint32_t GetSnakeSize();

private:
    uint32_t __SnakeSize = START_LENGTH;
    T_Pose __Snake[256];

    typedef enum T_Direction {RIGHT, UP, LEFT, DOWN};
    T_Direction __Snake_direction;
};

class Food {
public:
    void NewFood();
    void DeleteFood();
private:
    T_Pose __position;
    bool __state = 0;
};

class SnakeGame {
public:
    void GameStart();
    void UpdateGame();
    void EndGame();

private:
    Snake mySnake;
    Food food1;
    Food food2;
    Food food3;
    Food food4;
    Food food5;

    void GenerateWindow();
    void ClearWindow();

    friend void GenerateBufferLed();

    static bool __Snake_running;
    uint8_t __window[32];
    bool __is_dirty; //window need to be recalculated
};

extern SnakeGame mySnakeGame;







//class snake {
//    public:
//        void InitSnake();
//
//        void PlaySnake();
//
//    private:
//        friend void GenerateBufferLed();
//
//        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];
//
//        bool __SnakeBuffer;
//
//        typedef struct{ // Position de la nourriture
//            uint8_t __RandomFoodX;
//            uint8_t __RandomFoodY;
//        }TFood;
//        
//        typedef struct{ // Position du corps du serpent
//            uint8_t __BodyX;
//            uint8_t __BodyY;
//        } TSnakeBody;
//        
//        uint8_t __X;
//        uint8_t __Y;
//        uint8_t __Body;
//
//        typedef enum{  // Etat du jeu
//            PAUSE,
//            START
//        } TSnakeEtat;
//
//        typedef enum{ // Etat du serpent
//            HAUT,
//            GAUCHE, 
//            DROITE, 
//            BAS
//        } TSnakeSens;
//
//        TSnakeEtat snakeetat;
//        TSnakeSens snakesens;
//        TSnakeBody snakebody[START_LENGTH];
//        TFood snakefood[FOOD_NUMBER];
//
//        void GenerateFood();
//        void EatFood();
//        void ClearFood();
//
//        void PrintBody();
//        void GenerateBody();
//        
//        void MoveSnake();
//        void PrintHead();
//        
//};
//
//extern snake mySnake;
//
#endif