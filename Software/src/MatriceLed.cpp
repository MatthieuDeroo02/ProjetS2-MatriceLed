#include "MatriceLed.hpp"

void MatriceLed::begin(){
    Serial.begin(9600);
    DDRC = 0x0F;
    DDRD = 0x70;
}


void MatriceLed::SetLed(uint8_t x, uint8_t y, bool state) {
    
}

void MatriceLed::Show() {

}