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
    switch(snakesens){
        case HAUT:
            if(myClock.BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Gauche");
                #endif
                snakesens = GAUCHE;
            }
            if(myClock.BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Droite");
                #endif
                snakesens = DROITE;
            }
        
        case GAUCHE:
            if(myClock.BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Bas");
                #endif
                snakesens = BAS;
            }
            if(myClock.BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Haut");
                #endif
                snakesens = HAUT;
            }

        case DROITE:
            if(myClock.BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Haut");
                #endif
                snakesens = HAUT;
            }
            if(myClock.BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Bas");
                #endif
                snakesens = BAS;
            }

        case BAS:
            if(myClock.BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Droite");
                #endif
                snakesens = DROITE;
            }
            if(myClock.BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Gauche");
                #endif
                snakesens = GAUCHE;
            }
    }
}

void snake::PrintSnake(){
    switch(snakesens){
        case HAUT :
            __MatriceLed[i][j];
    }
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

/*------BP---------*/
bool BP1_Appuyer(){
    if((PIND & Masque_PD2) != 0){
        #if DEBUG_HORLOGE
            Serial.println("BP1 Appuyer");
        #endif
        return true; // BP1 Appuyer
    }
    else{
        return false; // BP1 Non Appuyer
    }
}

bool BP2_Appuyer(){
    if((PIND & Masque_PD3) != 0){
        #if DEBUG_HORLOGE
            Serial.println("BP2 Appuyer");
        #endif
        return true; // BP2 Appuyer
    }
    else{
        return false; // BP2 Non Appuyer
    }
}
