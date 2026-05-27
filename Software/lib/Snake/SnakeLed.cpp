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

    snakeetat = START;
    snakesens = START_SENS;

    GenerateFood();

    #if DEBUG_SNAKE
        Serial.println("Snake Init");
    #endif
}


void snake::SnakeGame(){
    switch(snakeetat){
        case START:
            if(BP1_Appuyer() || BP2_Appuyer()){
                snakeetat = PLAY;
            }
            break;

        case PLAY:
            if(SnakeTouch()){
                snakeetat = GAMEOVER;
            }
            break;

        case GAMEOVER:
            if(BP1_Appuyer() || BP2_Appuyer()){
                snakeetat = START;
            }
            break;
    }

    MoveSnake();

    ConvBuffer();
    //GenerateFood();
    GenerateBody();

    PrintHead();
    PrintBody();

    //EatFood();
}


void snake::PrintSnake(){  
    switch(snakeetat){
        case START:
            StartSnake();
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.println("ETAT : START");
            #endif
            break;

            case PLAY:
                PlaySnake();
                #if DEBUG_SNAKE
                    Serial.println("--------------");
                    Serial.println("ETAT : PLAY");
                #endif
                break;

            case GAMEOVER:
                SnakeGameOver();
                #if DEBUG_SNAKE
                    Serial.println("--------------");
                    Serial.println("ETAT : GAMEOVER");
                #endif
                break;
    }
}

void snake::StartSnake(){
        myMatrice.Print("SNAKE", 10, 0, MATRICE_SIZE_X-1);
}

void snake::PlaySnake(){
    MoveSnake();

    ConvBuffer();
    //GenerateFood();
    GenerateBody();

    PrintHead();
    PrintBody();

    //EatFood();
}

void snake::SnakeGameOver(){
    myMatrice.Print("GAME OVER", 10, 0, MATRICE_SIZE_X-1);
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
                Serial.println("SENS : HAUT");
            #endif
            if(__Y >= 8){__Y = 0;}
            break;

        case GAUCHE:
            __X--;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.println("SENS : GAUCHE");
            #endif
            if(__X <= 0){__X = 32;}
            break;

        case DROITE:
            __X++;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.println("SENS : DROITE");
            #endif
            if(__X >= 33){__X = 0;}
            break;

        case BAS:
            __Y--;
            #if DEBUG_SNAKE
                Serial.println("--------------");
                Serial.println("SENS : BAS");
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

bool snake::SnakeTouch(){
    for(int i = 0; i < __Body; i++){
        if((__X == snakebody[i].__BodyX) && (__Y == snakebody[i].__BodyY)){
            return true;
        }
    }
    return false;
}


/*------ BP1 ---------*/
bool BP1_Appuyer() {
    static bool etat_precedent = false; 
    
    bool etat_actuel = ((PIND & Masque_PD2) != 0);
    bool front_montant = false;

    if (etat_actuel && !etat_precedent) {
        front_montant = true;
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
    }

    etat_precedent = etat_actuel;

    return front_montant;
}

void snake::ConvBuffer() {
    for (int i = 0; i < MATRICE_SIZE_X; i++) {
        __BufferSnake[i] = 0; 
        for (int j = 0; j < MATRICE_SIZE_Y; j++) {
            if (__MatriceLed[i][j]) {
                __BufferSnake[i] |= (1 << j);
            }
        }
    }
}