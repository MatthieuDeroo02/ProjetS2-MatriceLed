#include "MatriceLed.hpp"

void MatriceLed::InitCLK() {
    noInterrupts();
/* Initialise le timer1 en mode CTC avec 2 comparateur*/
    TCCR1A = (TIMER1_CTC_OCR1A_COMPARE & 0b11); // Mode CTC avec debordement sur OCR1A
    TCCR1B = ((TIMER1_CTC_OCR1A_COMPARE & 0b1100)<<1) | TIMER1_PRESCALER_1; // Prescaleur de 1 -> frequence CLK a 244Hz minimume
    TCCR1C = 0; // Sert pas ici car force juste la comparaison

/* Calcule la valeur des comparateur*/
    OCR1A = 159; // Debordement timer -> clk_Up
    OCR1B = 79; // Iteruption Intermédiaire -> clk_Down and Update Data

/* Delclare les interuption*/
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);

    interrupts();
}

ISR(TIMER1_COMPA_vect) {
    PORTD |= (1<<PD5);
}

ISR(TIMER1_COMPB_vect) {
    PORTD &= ~(1<<PD5);
}

