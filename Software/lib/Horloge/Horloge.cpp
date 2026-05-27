#include "Horloge.hpp"

void clock::Begin() {
#if DEBUG_HORLOGE
    Serial.begin(SERIAL_MONITOR_BAUD);
#endif

    Wire.begin();
    TinyRtc.begin();
}

void clock::Begin(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,  uint8_t second) {
#if DEBUG_HORLOGE
    Serial.begin(SERIAL_MONITOR_BAUD);
#endif

    Wire.begin();
    TinyRtc.begin();

    /* Met a jour l'heure du module */
    TinyRtc.adjust(DateTime(year, month, day, hour, minute, second));
}

void clock::UpdateRTC() {
    time = TinyRtc.now();
}

char ConvChiffreAscii(uint8_t num){
    #if DEBUG_HORLOGE
        if(num > 9){
            Serial.println("ERREUR Conversion\n");
        }
    #endif
    return (char)(num +48);
}

#ifdef _MATRICE_LED_
    void clock::PrintTimeOnMatrice() {
        UpdateRTC();
        myMatrice.Clear();

        char str[6];
        str[0] = '0' + (GetHour()/10);
        str[1] = '0' + (GetHour()%10);
        str[2] = ':';
        str[3] = '0' + (GetMinute()/10);
        str[4] = '0' + (GetMinute()%10);
        str[5] = '\0';

        myMatrice.Print(str, 2);
    }
#endif