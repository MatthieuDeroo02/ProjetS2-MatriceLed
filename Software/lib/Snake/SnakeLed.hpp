#ifndef _SNAKE_
#define _SNAKE_

#include <Arduino.h>

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

#define START_X
#define START_Y

class snake {
    public:
        void InitSnake();

    private:
        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];
        
};

snake mySnake;

#endif