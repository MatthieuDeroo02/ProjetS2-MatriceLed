#ifndef _SNAKE_
#define _SNAKE_

#include "MatriceLed.hpp"
#include <Arduino.h>
#include <stdlib.h>
//#include <time.h>
//#include "Wire.h"

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

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

class snake {
    public:
        void InitSnake();

        void SnakeGame();
        
    private:
        friend void GenerateBufferLed();

        uint8_t __MatriceLed[MATRICE_SIZE_X][MATRICE_SIZE_Y];
        uint8_t __BufferSnake[MATRICE_SIZE_X];

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
            START,
            PLAY,
            GAMEOVER
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
        
        void MoveSnake();
        void PrintHead();

        bool SnakeTouch();

        void ConvBuffer();

        void SnakeGame();
        void PrintSnake();

        void PlaySnake();
        void StartSnake();
        void SnakeGameOver();


};

extern snake mySnake;

#endif