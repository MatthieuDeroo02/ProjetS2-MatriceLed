#include "MatriceLed.hpp"

void MatriceLed::InitLigneCLK() {
    noInterrupts();

/* Initialise le timer0 en mode CTC avec 1 comparateur*/
    TCCR0A = (TIMER0_CTC_OCRA_COMPARE & 0b11);
    TCCR0B = ((TIMER0_CTC_OCRA_COMPARE & 0b1100) << 1) | TIMER1_PRESCALER_64;

/* Calcule la valeur de basculement*/
    OCR0A = 124;

/* Declare l'interuption sur le debordement du timer0 */
    TIMSK0 = (1 << OCIE0A);

    interrupts();
}


ISR(TIMER0_COMPA_vect) {
    /* Push les donnée sur les leds et affiche*/

    /* Debut du travail sur la ligne suivante */
    ligneInProcesse = (ligneInProcesse+1)%8;

    /* Genere le buffer pour preparer le prochain affichage */
    GenerateBufferLed();

    /* Rallume les interuption Timer 1 */
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
}

void GenerateBufferLed() {
    uint8_t masque = (1 << ligneInProcesse);
    for (uint8_t i=0; i<32; i++) {
        data_buffer[i] = (Matrice.__MatriceLed[i] & masque) == masque;
    }
}