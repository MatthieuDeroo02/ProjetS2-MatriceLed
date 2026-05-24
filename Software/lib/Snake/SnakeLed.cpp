#include "SnakeLed.hpp"

snake mySnake;

void snake::InitSnake(){
    for(int i=0; i<MATRICE_SIZE_X; i++) {
        for (int j=0; j<MATRICE_SIZE_Y; j++) { 
            __MatriceLed[i][j] = 0; //Initialise la matrice en x/y a 0
        }
    }

    for(int i = START_X; i<START_LENGTH; i++) {
        __MatriceLed[START_X][START_Y - i] = 1; //Initialise le serpent a la position de départ
    }

    srand(time(NULL)); //Initialise le générateur de nombre aléatoire

    #if DEBUG_SNAKE
        Serial.println("Snake Initialisee");
    #endif
}

void snake::MoveSnake(){

}

void snake::PrintSnake(){

}

void snake::GenerateFood(){
    srand(time(NULL));

    for(int i = 0; i < FOOD_NUMBER; i++){
        
        uint8_t __RandomFoodX = rand() % MATRICE_SIZE_X;
        uint8_t __RandomFoodY = rand() % MATRICE_SIZE_Y;

        #if DEBUG_SNAKE
            Serial.print("Random FOOD X : ");
            Serial.println(__RandomFoodX);
            Serial.print("Random FOOD Y : ");
            Serial.println(__RandomFoodY);
        #endif
    }
}