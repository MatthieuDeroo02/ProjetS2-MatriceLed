#include "MatriceLed.hpp" 

void MatriceLed::UploadLigne() {

}

void MatriceLed::InitLigneCLK() {
    noInterrupts();

/* Initialise le timer0 en mode CTC avec 1 comparateur*/
    TCCR0A = (TIMER1_CTC_OCR1A_COMPARE & 0b11);
    TCCR0B = ((TIMER1_CTC_OCR1A_COMPARE & 0b1100) << 1);

    uint8_t prescaler;
    if (__MatriceLigneUpdatePeriod_US < 16)  {
        TCCR0B |= TIMER1_PRESCALER_1;
        OCR0A = __MatriceLigneUpdatePeriod_US/(CPU_CLK / 1);
    } else if (__MatriceLigneUpdatePeriod_US < 128) {
        TCCR0B |= TIMER1_PRESCALER_8;
        OCR0A = __MatriceLigneUpdatePeriod_US/(CPU_CLK / 8);
    } else if (__MatriceLigneUpdatePeriod_US < 1024) {
        TCCR0B |= TIMER1_PRESCALER_64;
        OCR0A = __MatriceLigneUpdatePeriod_US/(CPU_CLK / 64); 
    } else if (__MatriceLigneUpdatePeriod_US < 4095) {
        TCCR0B |= TIMER1_PRESCALER_256;
        OCR0A = __MatriceLigneUpdatePeriod_US/(CPU_CLK / 256); 
    } else {
        TCCR0B |= TIMER1_PRESCALER_1024;
        OCR0A = __MatriceLigneUpdatePeriod_US/(CPU_CLK / 1024);
    }

/* Declare l'interuption sur le debordement du timer0 */
    TIMSK0 = (OCIE1A << 1);

    interrupts();
}