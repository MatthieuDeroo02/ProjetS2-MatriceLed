#ifndef _SNAKE_
#define _SNAKE_

#include "Horloge.hpp"
#include "MatriceLed.hpp"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

#define START_X 16
#define START_Y 4
#define START_LENGTH 3
#define START_SENS 2   // 0 : HAUT, 1 : GAUCHE, 2 : DROITE, 3 : BAS

#define FOOD_NUMBER 1 

#define DEBUG_SNAKE 1


class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();


    private:
        friend void GenerateBufferLed();

        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];

        bool __SnakBuffer;

        uint8_t __RandomFoodX;
        uint8_t __RandomFoodY;

        typedef enum{
            PAUSE,
            START
        } TSnakeEtat;

        typedef enum{
            HAUT,
            GAUCHE, 
            DROITE, 
            BAS
        } TSnakeSens;

        TSnakeEtat snakeetat;
        TSnakeSens snakesens;

        void GenerateFood();
        
};

extern snake mySnake;

#endif