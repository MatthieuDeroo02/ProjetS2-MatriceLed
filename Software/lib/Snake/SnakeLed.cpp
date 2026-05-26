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

    randomSeed(analogRead(A0)); //Initialise le générateur de nombre aléatoire

    __SnakeBuffer = true;

    __Body = START_LENGTH;

    __X = START_X;
    __Y = START_Y;

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
            break;
        
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
            break;

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
            break;

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
            break;
    }
}

void snake::PrintSnake(){
    switch(snakesens){
        case HAUT:
            __Y++;
            if(__Y >= 32){__Y = 0;}
            break;

        case GAUCHE:
            __X--;
            if(__X <= 0){__X = 31;}
            break;

        case DROITE:
            __X++;
            if(__X >= 32){__X = 0;}
            break;

        case BAS:
            __Y--;
            if(__Y <= 0){__Y = 7;}
            break;

    }
}

void snake::GenerateFood(){
    randomSeed(analogRead(A0));

    for(int i = 0; i < FOOD_NUMBER; i++){ // Fonctionne pour le moment pour un fruit
        
        snakefood[i].__RandomFoodX = rand() % MATRICE_SIZE_X; 
        snakefood[i].__RandomFoodY = rand() % MATRICE_SIZE_Y;

        __MatriceLed[snakefood[i].__RandomFoodX][snakefood[i].__RandomFoodY] = 1;

        #if DEBUG_SNAKE
            Serial.print("Random FOOD X : ");
            Serial.println(snakefood[i].__RandomFoodX);
            Serial.print("Random FOOD Y : ");
            Serial.println(snakefood[i].__RandomFoodY);
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
void snake::GenerateBody(){
    for (int i = __Body - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
}

void snake::EatFood(){
    for(int i = 0; i < FOOD_NUMBER; i++){
        if((__X == snakefood[i].__RandomFoodX) && (__Y == snakefood[i].__RandomFoodY)){
            __Body++;
            GenerateFood();
        }
    }
}
