#include "MatriceLed.hpp"

MatriceLed::MatriceLed(uint16_t matrice_frequency, uint16_t CLK_frequency) {

/* Définition de la periode de rafréchissement de la matrice plafonnée a MATRICE_MAX_FREQUENCY*/
    if (matrice_frequency > MATRICE_MAX_FREQUENCY) {
        matrice_frequency = MATRICE_MAX_FREQUENCY;

#if DEBUG
        Serial.print("Frequence matrice plafonnee a");
        Serial.println(MATRICE_MAX_FREQUENCY);
#endif
    }
    __MatriceUpdatePeriod_NS = E9/matrice_frequency;


/* Calcule de la periode de rafréchissement ligne par ligne de la matrice*/
    __MatriceLigneUpdatePeriod_NS = __MatriceUpdatePeriod_NS/8;


/* Calcule de la frequence de la CLK plafonnée a CLK_MAX_FREQUENCY*/
    if (CLK_frequency > CLK_MAX_FREQUENCY) {
        CLK_frequency = CLK_MAX_FREQUENCY;

#if DEBUG
        Serial.print("Frequence clk plafonnee a");
        Serial.println(CLK_MAX_FREQUENCY);
#endif
    }
    __CLKFrequency = CLK_frequency;
}


void MatriceLed::SetLed(uint8_t x, uint8_t y, bool state) {
    
}