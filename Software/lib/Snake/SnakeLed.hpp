#ifndef _SNAKE_
#define _SNAKE_

#include "Horloge.hpp"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include "Wire.h"

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

#define START_X 16
#define START_Y 4
#define START_LENGTH 2

#define FOOD_NUMBER 1

#define DEBUG_SNAKE 1

#define SNAKE_SPEED


class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();


    private:
        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];
        uint8_t __SnakeHead[MATRICE_SIZE_X][MATRICE_SIZE_Y];

        bool __SnakeBuffer;

        typedef struct{
            uint8_t __RandomFoodX;
            uint8_t __RandomFoodY;
        }TFood;
        
        uint8_t __X;
        uint8_t __Y;
        uint8_t __Body;

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
        TFood snakefood[START_LENGTH];

        void GenerateFood();
        void SnakeBody();
        void GenerateBody();
        void EatFood();
        
};

extern snake mySnake;

#endif