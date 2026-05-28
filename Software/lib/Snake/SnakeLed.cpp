#include "SnakeLed.hpp"

SnakeGame mySnakeGame;
bool SnakeGame::__Snake_running = false;

void SnakeGame::GameStart() {
    /* Initilalise le serpent */
    mySnake.Begin();
    __Snake_running = true;

    /* Genere les 5 nouriture */

    /* Genere la 1ere image */
    GenerateWindow();
}

void SnakeGame::UpdateGame() {
    static unsigned long timer_snake_last_move = 0;

    /* Regarde si on change de direction */
    if (mySnake.GetAvailableToTurn()) {
        static bool tmp_bp1 = 0;
        static bool tmp_bp2 = 0;
        bool bp1 = BP1_Appuyer();
        bool bp2 = BP2_Appuyer();


        if (tmp_bp1 == 0 && bp1) {
            unsigned long timer_bp_debounce = newMillis();
            while(newMillis()-timer_bp_debounce < 30){};
                if (BP1_Appuyer()) mySnake.ChangeDirection(Snake::RIGHT);
        }
        if (tmp_bp2 == 0 && bp2) {
            unsigned long timer_bp_debounce = newMillis();
            while(newMillis()-timer_bp_debounce < 30){};
                if (BP2_Appuyer()) mySnake.ChangeDirection(Snake::LEFT);
        }

        tmp_bp1 = bp1;
        tmp_bp2 = bp2;
    }

    /* Si ca fait plus de 200ms on fait avancer le snake */
    if (newMillis()-timer_snake_last_move > 200) {
        mySnake.Avancer();
        timer_snake_last_move = newMillis();
        __is_dirty = true;
    }

    /* Si on doit rechager la fenetre */
    if (__is_dirty) {
        GenerateWindow();
        __is_dirty = false;
    }
}

void Snake::Avancer() {
    for (uint32_t index_pos_in_snake = __SnakeSize - 1; index_pos_in_snake > 0; index_pos_in_snake--) {
        __Snake[index_pos_in_snake] = __Snake[index_pos_in_snake-1];
    }
    switch(__Snake_direction) {
        case RIGHT:
            if (__Snake[0].x < MATRICE_SIZE_X-1) __Snake[0].x++;
            else __Snake[0].x = 0;
            break;
        case UP:
            if (__Snake[0].y > 0) __Snake[0].y--;
            else __Snake[0].y = MATRICE_SIZE_Y-1;
            break;
        case LEFT:
            if (__Snake[0].x > 0) __Snake[0].x--;
            else __Snake[0].x = MATRICE_SIZE_X-1;
            break;
        case DOWN:
            if (__Snake[0].y < MATRICE_SIZE_Y-1) __Snake[0].y++;
            else __Snake[0].y = 0;
            break;
    }
    __available_to_turn = true;
}

void Snake::Begin() {
    /* Genere un snake de depart de 3 de long */
    __SnakeSize = 3;
    __Snake_direction = RIGHT;
    __Snake[0] = {16, 4};
    __Snake[1] = {15, 4};
    __Snake[2] = {14, 4};

    __available_to_turn = true;
}

void SnakeGame::GenerateWindow() {
    ClearWindow();

    /* Ajoute le serpent */
    T_Pose *snake = mySnake.GetSnake(); 
    for (uint32_t index_snake = 0; index_snake < mySnake.GetSnakeSize(); index_snake++) {
        __window[snake[index_snake].x] |= (1<<snake[index_snake].y);
    }

    /* Ajoute les fruits */
}

void SnakeGame::ClearWindow() {
    for (uint8_t index=0; index < MATRICE_SIZE_X; index++) {
        __window[index] = 0;
    }
}

T_Pose* Snake::GetSnake() {
    return __Snake;
}

uint32_t Snake::GetSnakeSize() {
    return __SnakeSize;
}

void Snake::ChangeDirection(T_Direction turn) {
    switch (turn) {
        case RIGHT:
            switch (__Snake_direction) {
                case RIGHT: __Snake_direction = DOWN; break;
                case UP: __Snake_direction = RIGHT; break;
                case LEFT: __Snake_direction = UP; break;
                case DOWN: __Snake_direction = LEFT; break;
            }
            __available_to_turn = false;
            break;
        case LEFT:
            switch (__Snake_direction) {
                case RIGHT: __Snake_direction = UP; break;
                case UP: __Snake_direction = LEFT; break;
                case LEFT: __Snake_direction = DOWN; break;
                case DOWN: __Snake_direction = RIGHT; break;
            }
            __available_to_turn = false;
            break;
        default: break;
    }
}

bool Snake::GetAvailableToTurn() {
    return __available_to_turn;
}




/*------BP---------*/
bool BP1_Appuyer(){
    return ((PIND & (1<<BP1)) == (1<<BP1));
}

bool BP2_Appuyer(){
    return ((PIND & (1<<BP2)) == (1<<BP2));
}

void BP_Init() {
    DDRD &= ~((1<<BP1) | (1<<BP2));
    //PORTD |= (1<<BP1) | (1<<BP2);
}

//snake mySnake;
//
//void snake::InitSnake(){
//    #if DEBUG_SNAKE
//        Serial.begin(SERIAL_MONITOR_BAUD);
//    #endif
//
//    for(int i=0; i<MATRICE_SIZE_X; i++) {
//        for (int j=0; j<MATRICE_SIZE_Y; j++) { 
//            __MatriceLed[i][j] = 0; //Initialise la matrice en x/y a 0
//        }
//    }
//
//    for(int i = START_X; i<START_LENGTH; i++) {
//        __MatriceLed[START_X][START_Y - i] = 1; //Initialise le serpent a la position de départ
//    }
//
//    randomSeed(analogRead(A0)); //Initialise le générateur de nombre aléatoire
//
//    __SnakeBuffer = true;
//
//    __Body = START_LENGTH;
//
//    __X = START_X;
//    __Y = START_Y;
//
//    #if DEBUG_SNAKE
//        Serial.println("Snake Init");
//    #endif
//}
//
//
//
//void snake::PlaySnake(){
//    MoveSnake();
//
//    GenerateFood();
//    GenerateBody();
//
//    PrintHead();
//    PrintBody();
//
//    EatFood();
//}
//
//
//
//void snake::MoveSnake(){
//    switch(snakesens){
//        case HAUT:
//            if(BP1_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP1 Appuyer = Gauche");
//                #endif
//                snakesens = GAUCHE;
//            }
//            if(BP2_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP2 Appuyer = Droite");
//                #endif
//                snakesens = DROITE;
//            }
//            break;
//        
//        case GAUCHE:
//            if(BP1_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP1 Appuyer = Bas");
//                #endif
//                snakesens = BAS;
//            }
//            if(BP2_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP2 Appuyer = Haut");
//                #endif
//                snakesens = HAUT;
//            }
//            break;
//        
//        case DROITE:
//            if(BP1_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP1 Appuyer = Haut");
//                #endif
//                snakesens = HAUT;
//            }
//            if(BP2_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP2 Appuyer = Bas");
//                #endif
//                snakesens = BAS;
//            }
//            break;
//
//        case BAS:
//            if(BP1_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP1 Appuyer = Droite");
//                #endif
//                snakesens = DROITE;
//            }
//            if(BP2_Appuyer()){
//                #if DEBUG_SNAKE
//                    Serial.print(snakesens);
//                    Serial.println("| BP2 Appuyer = Gauche");
//                #endif
//                snakesens = GAUCHE;
//            }
//            break;
//    }
//}
//
//void snake::PrintHead(){
//    switch(snakesens){
//        case HAUT:
//            __Y++;
//            if(__Y >= 32){__Y = 0;}
//            break;
//
//        case GAUCHE:
//            __X--;
//            if(__X <= 0){__X = 31;}
//            break;
//
//        case DROITE:
//            __X++;
//            if(__X >= 32){__X = 0;}
//            break;
//
//        case BAS:
//            __Y--;
//            if(__Y <= 0){__Y = 7;}
//            break;
//
//    }
//    #if DEBUG_SNAKE
//        Serial.println("----------------\n");
//        Serial.print("Snake Move to : ");
//        Serial.print(__X);
//        Serial.print("|");
//        Serial.println(__Y);
//    #endif
//
//    snakebody[0].__BodyX = 1;
//    snakebody[0].__BodyY = 1;
//}
//
//void snake::PrintBody(){
//    for(int i = 0; i < __Body; i++){
//        __MatriceLed[snakebody[i].__BodyX][snakebody[i].__BodyY] = 1;
//    }
//}
//
//void snake::GenerateFood(){
//    randomSeed(analogRead(A0));
//
//    for(int i = 0; i < FOOD_NUMBER; i++){ 
//        snakefood[i].__RandomFoodX = rand() % MATRICE_SIZE_X;
//        snakefood[i].__RandomFoodY = rand() % MATRICE_SIZE_Y;
//
//        __MatriceLed[snakefood[i].__RandomFoodX][snakefood[i].__RandomFoodY] = 1;
//
//        #if DEBUG_SNAKE
//            Serial.println("----------FOOD %i---------\n, i");
//            Serial.print("Random FOOD X : ");
//            Serial.println(snakefood[i].__RandomFoodX);
//            Serial.print("Random FOOD Y : ");
//            Serial.println(snakefood[i].__RandomFoodY);
//        #endif
//    }
//}
//
//void snake::GenerateBody(){
//    for (int i = __Body - 1; i > 0; i--) {
//        snakebody[i].__BodyX = snakebody[i - 1].__BodyX;
//        snakebody[i].__BodyY = snakebody[i - 1].__BodyY;
//    }
//}
//
//void snake::EatFood(){
//    for(int i = 0; i < FOOD_NUMBER; i++){
//        if((__X == snakefood[i].__RandomFoodX) && (__Y == snakefood[i].__RandomFoodY)){
//
//            __Body++;
//
//            ClearFood();
//            GenerateFood();
//
//            #if DEBUG_SNAKE
//                Serial.println("-----Food eaten-----\n");
//                Serial.print("Body Size : ");
//                Serial.println(__Body);
//            #endif
//        }
//    }
//}
//
//void snake::ClearFood(){
//        for(int i = 0; i < FOOD_NUMBER; i++){
//            __MatriceLed[snakefood[i].__RandomFoodX][snakefood[i].__RandomFoodY] = 0;
//        }
//        #if DEBUG_SNAKE
//            Serial.println("-----Food Clear-----\n");
//        #endif
//}
//
///*------BP---------*/
//bool BP1_Appuyer(){
//    if((PIND & Masque_PD2) != 0){
//        #if DEBUG_SNAKE
//            Serial.println("BP1 Appuyer");
//        #endif
//        return true; // BP1 Appuyer
//    }
//    else{
//        return false; // BP1 Non Appuyer
//    }
//}
//
//bool BP2_Appuyer(){
//    if((PIND & Masque_PD3) != 0){
//        #if DEBUG_SNAKE
//            Serial.println("BP2 Appuyer");
//        #endif
//        return true; // BP2 Appuyer
//    }
//    else{
//        return false; // BP2 Non Appuyer
//    }
//}