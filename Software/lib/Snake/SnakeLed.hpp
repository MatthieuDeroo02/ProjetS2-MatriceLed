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
#define START_LENGTH 3

#define FOOD_NUMBER 1

#define DEBUG_SNAKE 1

#define SNAKE_SPEED

bool BP1_Appuyer();
bool BP2_Appuyer();

class snake {
    public:
        void InitSnake();

        void MoveSnake();
        void PrintSnake();

    private:
        friend void GenerateBufferLed();

        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];
        //uint8_t __SnakeHead[START_LENGTH]; 

        bool __SnakeBuffer;

        typedef struct{ // Position de la nourriture
            uint8_t __RandomFoodX;
            uint8_t __RandomFoodY;
        }TFood;
        
        typedef struct{ // Position du corps du serpent
            uint8_t __BodyX;
            uint8_t __BodyY;
        } TSnakeBody;
        
        uint8_t __X;
        uint8_t __Y;
        uint8_t __Body;

        typedef enum{  // Etat du jeu
            PAUSE,
            START
        } TSnakeEtat;

        typedef enum{ // Etat du serpent
            HAUT,
            GAUCHE, 
            DROITE, 
            BAS
        } TSnakeSens;

        TSnakeEtat snakeetat;
        TSnakeSens snakesens;
        TSnakeBody snakebody[START_LENGTH];
        TFood snakefood[FOOD_NUMBER];

        void GenerateFood();
        void EatFood();
        void ClearFood();

        void PrintBody();
        void GenerateBody();
        
        
};

extern snake mySnake;

#endif