#include "SnakeLed.hpp"

snake mySnake;

void snake::InitSnake(){
    #if DEBUG_SNAKE
        Serial.begin(SERIAL_MONITOR_BAUD);
    #endif

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
        Serial.println("Snake Init");
    #endif
}



void snake::PlaySnake(){
    MoveSnake();

    //GenerateFood();
    GenerateBody();

    PrintHead();
    PrintBody();

    EatFood();
}



void snake::MoveSnake(){
    switch(snakesens){
        case HAUT:
            if(BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Gauche");
                #endif
                snakesens = GAUCHE;
            }
            if(BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Droite");
                #endif
                snakesens = DROITE;
            }
            break;
        
        case GAUCHE:
            if(BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Bas");
                #endif
                snakesens = BAS;
            }
            if(BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Haut");
                #endif
                snakesens = HAUT;
            }
            break;
        
        case DROITE:
            if(BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Haut");
                #endif
                snakesens = HAUT;
            }
            if(BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Bas");
                #endif
                snakesens = BAS;
            }
            break;

        case BAS:
            if(BP1_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP1 Appuyer = Droite");
                #endif
                snakesens = DROITE;
            }
            if(BP2_Appuyer()){
                #if DEBUG_SNAKE
                    Serial.print(snakesens);
                    Serial.println("| BP2 Appuyer = Gauche");
                #endif
                snakesens = GAUCHE;
            }
            break;
    }
}

void snake::PrintHead(){
    switch(snakesens){
        case HAUT:
            __Y++;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.print("SENS : HAUT");
            #endif
            if(__Y >= 32){__Y = 0;}
            break;

        case GAUCHE:
            __X--;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.print("SENS : GAUCHE");
            #endif
            if(__X <= 0){__X = 31;}
            break;

        case DROITE:
            __X++;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.print("SENS : DROITE");
            #endif
            if(__X >= 32){__X = 0;}
            break;

        case BAS:
            __Y--;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.print("SENS : BAS");
            #endif
            if(__Y <= 0){__Y = 7;}
            break;

    }
    #if DEBUG_SNAKE
        Serial.println("--------------");
        Serial.print("Snake Move to X :");
        Serial.print(__X);
        Serial.print("| Y :");
        Serial.println(__Y);
    #endif

    snakebody[0].__BodyX = 1;
    snakebody[0].__BodyY = 1;
}

void snake::PrintBody(){
    for(int i = 0; i < __Body; i++){
        __MatriceLed[snakebody[i].__BodyX][snakebody[i].__BodyY] = 1;
    }
}

void snake::GenerateFood(){
    randomSeed(analogRead(A0));

    for(int i = 0; i < FOOD_NUMBER; i++){ 
        snakefood[i].__RandomFoodX = rand() % MATRICE_SIZE_X;
        snakefood[i].__RandomFoodY = rand() % MATRICE_SIZE_Y;

        __MatriceLed[snakefood[i].__RandomFoodX][snakefood[i].__RandomFoodY] = 1;

        #if DEBUG_SNAKE
            Serial.print("----------FOOD ");
            Serial.print(i);
            Serial.println("----------");
            Serial.print("Random FOOD X : ");
            Serial.println(snakefood[i].__RandomFoodX);
            Serial.print("Random FOOD Y : ");
            Serial.println(snakefood[i].__RandomFoodY);
        #endif
    }
}

void snake::GenerateBody(){
    for (int i = __Body - 1; i > 0; i--) {
        snakebody[i].__BodyX = snakebody[i - 1].__BodyX;
        snakebody[i].__BodyY = snakebody[i - 1].__BodyY;
    }
}

void snake::EatFood(){
    for(int i = 0; i < FOOD_NUMBER; i++){
        if((__X == snakefood[i].__RandomFoodX) && (__Y == snakefood[i].__RandomFoodY)){

            __Body++;

            ClearFood();
            GenerateFood();

            #if DEBUG_SNAKE
                Serial.println("-----Food eaten-----\n");
                Serial.print("Body Size : ");
                Serial.println(__Body);
            #endif
        }
    }
}

void snake::ClearFood(){
        for(int i = 0; i < FOOD_NUMBER; i++){
            __MatriceLed[snakefood[i].__RandomFoodX][snakefood[i].__RandomFoodY] = 0;
        }
        #if DEBUG_SNAKE
            Serial.println("-----Food Clear-----\n");
        #endif
}


/*------ BP1 ---------*/
bool BP1_Appuyer() {
    static bool etat_precedent = false; 
    
    bool etat_actuel = ((PIND & Masque_PD2) != 0);
    bool front_montant = false;

    if (etat_actuel && !etat_precedent) {
        front_montant = true;
        #if DEBUG_SNAKE
            Serial.println("BP1 : Front Montant Détecté (Appui)");
        #endif
    }

    etat_precedent = etat_actuel;

    return front_montant;
}

/*------ BP2 ---------*/
bool BP2_Appuyer() {
    static bool etat_precedent = false;
    
    bool etat_actuel = ((PIND & Masque_PD3) != 0);
    bool front_montant = false;

    if (etat_actuel && !etat_precedent) {
        front_montant = true;
        #if DEBUG_SNAKE
            Serial.println("BP2 : Front Montant Détecté (Appui)");
        #endif
    }

    etat_precedent = etat_actuel;

    return front_montant;
}