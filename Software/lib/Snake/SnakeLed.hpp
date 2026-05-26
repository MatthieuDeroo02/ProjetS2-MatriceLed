#ifndef _SNAKE_
#define _SNAKE_

#include "Horloge.hpp"
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

bool BP1_Appuyer();
bool BP2_Appuyer();


class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();


    private:
        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];

        uint8_t __RandomFoodX;
        uint8_t __RandomFoodY;

        typedef enum{
        HAUT,
        GAUCHE, 
        DROITE, 
        BAS
        } TSnakeSens;

        TSnakeSens snakesens;

        void GenerateFood();
        
};

extern snake mySnake;

#endif