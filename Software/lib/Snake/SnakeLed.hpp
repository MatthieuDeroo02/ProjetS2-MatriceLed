#ifndef _SNAKE_
#define _SNAKE_

#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

#define START_X 16
#define START_Y 4
#define START_LENGTH 3

#define FOOD_NUMBER 1


class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();


    private:
        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];

        uint8_t RandomFoodX();
        uint8_t RandomFoodY();

        void GenerateFood();
        
};

snake mySnake;

#endif