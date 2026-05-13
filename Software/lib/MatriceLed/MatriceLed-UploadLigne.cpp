#include "MatriceLed.hpp"

void MatriceLed::InitLigneCLK() {
    noInterrupts();

/* Initialise le timer0 en mode CTC avec 1 comparateur*/
    TCCR0A = (TIMER0_CTC_OCRA_COMPARE & 0b11);
    TCCR0B = ((TIMER0_CTC_OCRA_COMPARE & 0b1100) << 1) | TIMER1_PRESCALER_64;

/* Calcule la valeur de basculement*/
    OCR0A = 124;

/* Declare l'interuption sur le debordement du timer0 */
    TIMSK0 = (OCIE1A << 1);

    interrupts();
}


ISR(TIMER0_COMPA_vect) {
    PORTD ^= (1<<PD5);
    //Serial.println(PIND);
}