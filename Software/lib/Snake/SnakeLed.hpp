#ifndef _SNAKE_
#define _SNAKE_

#include "Horloge.hpp"
#include "MatriceLed.hpp"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include "Wire.h"

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

#define START_X 16
#define START_Y 4
#define START_LENGTH 3
#define START_SENS 2   // 0 : HAUT, 1 : GAUCHE, 2 : DROITE, 3 : BAS

#define FOOD_NUMBER 1 

#define DEBUG_SNAKE 1

<<<<<<< HEAD
bool BP1_Appuyer();
bool BP2_Appuyer();
=======
>>>>>>> 34d147b (update snake buffer)
bool __SnakBuffer;


class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();


    private:
        friend void GenerateBufferLed();
<<<<<<< HEAD

=======
        
>>>>>>> 34d147b (update snake buffer)
        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];

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
        void GenerateBody();

        void EatFood();
        
};

extern snake mySnake;

#endif