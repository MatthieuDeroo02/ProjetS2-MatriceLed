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

class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();


    private:
        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];
        
};

snake mySnake;

#endif