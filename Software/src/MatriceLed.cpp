#include "MatriceLed.hpp"

<<<<<<< HEAD
void begin(){
    
}

=======
void MatriceLed::begin(){
    Serial.begin(9600);
    DDRC = 0x0F;
    DDRD = 0x70;
}


>>>>>>> bc872a5 (add DDR)
void MatriceLed::SetLed(uint8_t x, uint8_t y, bool state) {
    
}