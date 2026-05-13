#include "MatriceLed.hpp"

void MatriceLed::InitCLK() {
    noInterrupts();
/* Initialise le timer1 en mode CTC avec 2 comparateur*/
    TCCR1A = (TIMER1_CTC_OCR1A_COMPARE & 0b11); // Mode CTC avec debordement sur OCR1A
    TCCR1B = ((TIMER1_CTC_OCR1A_COMPARE & 0b1100)<<1) | TIMER1_PRESCALER_1; // Prescaleur de 1 -> frequence CLK a 244Hz minimume
    TCCR1C = 0; // Sert pas ici car force juste la comparaison

/* Calcule la valeur des comparateur*/
    OCR1A = (CPU_CLK / __CLKFrequency) - 1; // Debordement timer -> clk_Up
    OCR1B = (OCR1A/2); // Iteruption Intermédiaire -> clk_Down and Update Data

#if DEBUG
    Serial.print("OCR1A = ");
    Serial.print(OCR1A);
    Serial.print("  ->  ");
    Serial.print((62.5*OCR1A));
    Serial.println("µS");
#endif

    interrupts();
}