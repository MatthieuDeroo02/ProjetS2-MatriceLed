#include "Horloge.hpp"

void clock::Begin() {
#if DEBUG_HORLOGE
    Serial.begin(9600);
#endif

    Wire.begin();
    TinyRtc.begin();
}

void clock::Begin(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,  uint8_t second) {
#if DEBUG_HORLOGE
    Serial.begin(9600);
#endif

    Wire.begin();
    TinyRtc.begin();

    /* Met a jour l'heure du module */
    TinyRtc.adjust(DateTime(year, month, day, hour, minute, second));
}

void clock::UpdateRTC() {
    time = TinyRtc.now();
}

uint16_t ConvChiffreAscii(uint8_t num){
    #if DEBUG_HORLOGE
        if(num > 9){
            Serial.println("ERREUR Conversion\n");
        }
    #endif
    return num +48;
}