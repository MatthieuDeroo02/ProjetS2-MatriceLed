#include "SnakeLed.hpp"

SnakeGame mySnakeGame;
bool SnakeGame::__Snake_running = false;

void SnakeGame::GameStart() {
    /* Genere la seed */
    myClock.UpdateRTC();
    randomSeed(myClock.GetSecond());

    /* Recupere les score max */
    __rtc_memory_error = false;
    myMemoire.Begin(RTC_EEPROM_I2C_ADDR);
    __master_score = ((uint32_t)myMemoire.ReadByte(MASTER_SCORE_ADDR,   &__rtc_memory_error) << 24)
               | ((uint32_t)myMemoire.ReadByte(MASTER_SCORE_ADDR+1, &__rtc_memory_error) << 16)
               | ((uint32_t)myMemoire.ReadByte(MASTER_SCORE_ADDR+2, &__rtc_memory_error) << 8)
               |            myMemoire.ReadByte(MASTER_SCORE_ADDR+3, &__rtc_memory_error);
    __master_acs = myMemoire.ReadByte(MASTER_ACS_ADDR, &__rtc_memory_error);
    /* Initilalise le serpent */
    mySnake.Begin();
    __Snake_running = true;

    /* Genere les 5 nouriture */
    food1.NewFood(GenerateRandomPose());
    food2.NewFood(GenerateRandomPose());
    food3.NewFood(GenerateRandomPose());
    food4.NewFood(GenerateRandomPose());
    food5.NewFood(GenerateRandomPose());


    /* Genere la 1ere image */
    GenerateWindow();

    /* Debut le compteur */
    __SnakeStart = newMillis();
}

bool SnakeGame::UpdateGame() {
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
        /* On regarde si il touche une pomme */
        mySnake.EatFood(&food1);
        mySnake.EatFood(&food2);
        mySnake.EatFood(&food3);
        mySnake.EatFood(&food4);
        mySnake.EatFood(&food5);


        if (mySnake.GetTouchWall() || mySnake.GetTouchHimself()) {
            return false;
        }
        __is_dirty = true;
    }

    /* Si il y a encore de l'espace libre sur la matrice */
    if (mySnake.GetSnakeSize() < 256-5) {
        if (food1.GetState() == false)  food1.NewFood(GenerateRandomPose());
        if (food2.GetState() == false)  food2.NewFood(GenerateRandomPose());
        if (food3.GetState() == false)  food3.NewFood(GenerateRandomPose());
        if (food4.GetState() == false)  food4.NewFood(GenerateRandomPose());
        if (food5.GetState() == false)  food5.NewFood(GenerateRandomPose());
    }

    /* Si on doit rechager la fenetre */
    if (__is_dirty) {
        GenerateWindow();
        __is_dirty = false;
    }
    return true;
}
void Snake::Begin() {
    /* Genere un snake de depart de 3 de long */
    __SnakeSize = 3;
    __Snake_direction = RIGHT;
    __Snake[0] = {16, 4};
    __Snake[1] = {15, 4};
    __Snake[2] = {14, 4};

    __touch_wall = false;
    __touch_himself = false;
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
    if(food1.GetState()) SetLedWindow(food1.GetPose().x, food1.GetPose().y, true);
    if(food2.GetState()) SetLedWindow(food2.GetPose().x, food2.GetPose().y, true);
    if(food3.GetState()) SetLedWindow(food3.GetPose().x, food3.GetPose().y, true);
    if(food4.GetState()) SetLedWindow(food4.GetPose().x, food4.GetPose().y, true);
    if(food5.GetState()) SetLedWindow(food5.GetPose().x, food5.GetPose().y, true);
}

void SnakeGame::SetLedWindow(uint8_t x, uint8_t y, bool state) {
    __window[x] = (__window[x] & ~(1<<y)) | (state << y);
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

bool Snake::GetTouchWall() {
    return __touch_wall;
}
bool Snake::GetTouchHimself() {
    return __touch_himself;
}

void Snake::Avancer() {
    for (uint32_t index_pos_in_snake = __SnakeSize - 1; index_pos_in_snake > 0; index_pos_in_snake--) {
        __Snake[index_pos_in_snake] = __Snake[index_pos_in_snake-1];
    }
    switch(__Snake_direction) {
        case RIGHT:
            if (__Snake[0].x < MATRICE_SIZE_X-1) __Snake[0].x++;
            else __touch_wall = true;
            break;
        case UP:
            if (__Snake[0].y > 0) __Snake[0].y--;
            else __touch_wall = true;
            break;
        case LEFT:
            if (__Snake[0].x > 0) __Snake[0].x--;
            else __touch_wall = true;
            break;
        case DOWN:
            if (__Snake[0].y < MATRICE_SIZE_Y-1) __Snake[0].y++;
            else __touch_wall = true;
            break;
    }

    /* Regarde si il se touche */
    for (uint8_t index = 5; index < __SnakeSize; index++) {
        if ((__Snake[0].x == __Snake[index].x) && (__Snake[0].y == __Snake[index].y)) __touch_himself = true;
    }

    __available_to_turn = true;
}

void SnakeGame::EndGame() {
    unsigned long tempo = newMillis();

    uint32_t score = mySnake.GetSnakeSize();
    // Correction : acs doit être uint32_t pour éviter l'overflow avec score * temps
    uint32_t acs = (uint32_t)score * (newMillis() - __SnakeStart) / 1000;

    bool new_score = false;
    bool new_acs   = false;

    if (score > __master_score) {
        __master_score = score;
        myMemoire.WriteByte(MASTER_SCORE_ADDR,     (score >> 24) & 0xFF);
        myMemoire.WriteByte(MASTER_SCORE_ADDR + 1, (score >> 16) & 0xFF);  // bug fix : adresses décalées
        myMemoire.WriteByte(MASTER_SCORE_ADDR + 2, (score >> 8)  & 0xFF);
        myMemoire.WriteByte(MASTER_SCORE_ADDR + 3,  score        & 0xFF);
        new_score = true;
    }

    if (acs > __master_acs) {
        __master_acs = acs;
        myMemoire.WriteByte(MASTER_ACS_ADDR, acs);
        new_acs = true;
    }

    // --- Construction du message défilant ---
    // Format : "LOSE  SCO:1234  [NEW!] ACS:5678  [NEW!]"
    char msg[64];
    uint8_t pos = 0;

    // "LOSE  "
    const char* intro = "LOSE  ";
    for (uint8_t i = 0; intro[i]; i++) msg[pos++] = intro[i];

    // "SCO:" + valeur score
    const char* sco_lbl = "SCO:";
    for (uint8_t i = 0; sco_lbl[i]; i++) msg[pos++] = sco_lbl[i];
    pos += _uint32ToStr(score, &msg[pos]);
    msg[pos++] = ' ';
    msg[pos++] = ' ';

    if (new_score) {
        const char* tag = "NEW!  ";
        for (uint8_t i = 0; tag[i]; i++) msg[pos++] = tag[i];
    }

    // "ACS:" + valeur acs
    const char* acs_lbl = "ACS:";
    for (uint8_t i = 0; acs_lbl[i]; i++) msg[pos++] = acs_lbl[i];
    pos += _uint32ToStr(acs, &msg[pos]);
    msg[pos++] = ' ';
    msg[pos++] = ' ';

    if (new_acs) {
        const char* tag = "NEW!  ";
        for (uint8_t i = 0; tag[i]; i++) msg[pos++] = tag[i];
    }

    msg[pos] = '\0';

    // --- Défilement ---
    while (newMillis() - tempo < 1000) {}  // pause 1s avant animation
    __Snake_running = false;

    // x de départ : juste après le bord droit de la matrice
    // x de fin    : dernier caractère sorti à gauche (~6px par char)
    const int8_t CHAR_WIDTH = 5;  // largeur d'un caractère + espace (à ajuster selon ta fonte)
    int16_t x_start = MATRICE_SIZE_X;
    int16_t x_end   = -(int16_t)(pos * CHAR_WIDTH);

    int16_t x_scroll = x_start;
    unsigned long last_scroll = newMillis();
    const uint8_t SCROLL_DELAY_MS = 100;  // vitesse : plus petit = plus rapide

    bool done = false;
    while (!done) {
        unsigned long now = newMillis();

        // Avancer le scroll
        if (now - last_scroll >= SCROLL_DELAY_MS) {
            last_scroll = now;
            myMatrice.Clear();
            myMatrice.Print(msg, (int8_t)x_scroll);
            x_scroll--;

            // Quand le texte est entièrement sorti, on reboucle
            if (x_scroll < x_end) {
                x_scroll = x_start;
            }
        }

        if (BP1_Appuyer() || BP2_Appuyer()) {
            done = true;
        }
    }

    myMatrice.Clear();
}

// Utilitaire : écrit un uint32_t en ASCII dans buf, retourne le nb de chars écrits
uint8_t SnakeGame::_uint32ToStr(uint32_t val, char* buf) {
    if (val == 0) { buf[0] = '0'; buf[1] = '\0'; return 1; }
    char tmp[11];
    uint8_t i = 0;
    while (val > 0) {
        tmp[i++] = '0' + (val % 10);
        val /= 10;
    }
    // inverser
    for (uint8_t j = 0; j < i; j++) buf[j] = tmp[i - 1 - j];
    buf[i] = '\0';
    return i;
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

void Food::NewFood(T_Pose position) {
    __position = position;
    __state = true;
}

bool Food::GetState() {
    return __state;
}

T_Pose SnakeGame::GenerateRandomPose() {
    T_Pose position;
    do {
        position.x = random(MATRICE_SIZE_X-1);
        position.y = random(MATRICE_SIZE_Y-1);
    } while (PositionIsFull(position));

    return position;
}

bool SnakeGame::PositionIsFull(T_Pose position) {
    /* Regarde si le snake est dessue */
    T_Pose* snake = mySnake.GetSnake();
    for (uint8_t index = 0; index < mySnake.GetSnakeSize(); index++) {
        if (snake[index].x == position.x && snake[index].y == position.y) return true;
    }

    /* Regarde si il y a deja une nouriture dessue */
    if(food1.GetState() && (food1.GetPose().x == position.x) && (food1.GetPose().y == position.y)) return true;
    if(food2.GetState() && (food2.GetPose().x == position.x) && (food2.GetPose().y == position.y)) return true;
    if(food3.GetState() && (food3.GetPose().x == position.x) && (food3.GetPose().y == position.y)) return true;
    if(food4.GetState() && (food4.GetPose().x == position.x) && (food4.GetPose().y == position.y)) return true;
    if(food5.GetState() && (food5.GetPose().x == position.x) && (food5.GetPose().y == position.y)) return true;

    return false;
}

T_Pose Food::GetPose() {
    return __position;
}

bool Snake::EatFood(Food *myFood) {
    if ((__Snake[0].x == myFood->GetPose().x) && (__Snake[0].y == myFood->GetPose().y)) {
        myFood->SetState(false);
        __SnakeSize++;
        return true;
    }
    return false;
}

void Food::SetState(bool state) {
    __state = state;
}

void SnakeGame::CloseGame() {

}