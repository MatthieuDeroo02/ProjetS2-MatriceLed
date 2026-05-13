#include "MatriceLed.hpp"

void MatriceLed::begin(){
    /*
    Serial.begin(9600);
    DDRC = 0x0F;
    DDRD = 0x70;*/

    InitLigneCLK();
    InitCLK();
}