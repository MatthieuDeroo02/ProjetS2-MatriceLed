#include "MatriceLed.hpp"

void MatriceLed::begin(){
    /*
    Serial.begin(9600);
    DDRC = 0x0F;
    DDRD = 0x70;*/

    InitLigneCLK();
    InitCLK();
}

void MatriceLed::PinConfig() {
    DDRD |= (1<<DATA_PIN) | (1<<CLK_PIN) | (1<<STR_PIN);
    DDRC |= (1<<ALO) | (1<<AL1) | (1<<AL2) | (1<<CS1);
}