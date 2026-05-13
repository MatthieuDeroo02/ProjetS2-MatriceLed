#include "MatriceLed.hpp"

void MatriceLed::InitCLK() {
    noInterrupts();
/* Initialise le timer1 en mode CTC avec 2 comparateur*/
    TCCR1A = (TIMER1_CTC_OCR1A_COMPARE & 0b11); // Mode CTC avec debordement sur OCR1A
    TCCR1B = ((TIMER1_CTC_OCR1A_COMPARE & 0b1100)<<1) | TIMER1_PRESCALER_1; // Prescaleur de 1 -> frequence CLK a 244Hz minimume
    TCCR1C = 0; // Sert pas ici car force juste la comparaison

/* Calcule la valeur des comparateur*/
    OCR1A = 159; // Debordement timer -> clk_Up
    OCR1B = 70; // Interuption Intermédiaire -> clk_Down and Update Data

/* Delclare les interuption*/
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);

    interrupts();
}

ISR(TIMER1_COMPA_vect) {
    /*Down la Clock*/
    PORTD |= (1<<PD5);

    /*Upload data*/
    PORTD |= (PORTD &~(1<<DATA_PIN)) | (data_buffer[data_index] << DATA_PIN);

    /*Incremente data_index*/
    data_index++;
}

ISR(TIMER1_COMPB_vect) {
    /*Up la clock*/
    PORTD &= ~(1<<DATA_PIN);

    /* Si on a finit les 32 bits on arrete l'a clk et data*/
    if (data_index >= 32) {
        TIMSK1 = 0; // Arrete les interuption sur TIMER1
    }
}

