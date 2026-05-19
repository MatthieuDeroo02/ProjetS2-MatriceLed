#include "MatriceLed.hpp"

volatile uint8_t data_index = 0;
volatile bool data_buffer[32] = {0};
volatile uint8_t ligneInProcesse = 0;

MatriceLed myMatrice;



void MatriceLed::begin(){

#if DEBUG
    Serial.begin(9600);
#endif

    /* Initilaise les Pin GPIO */
    PinConfig();

    /* Initilaise les differentes clock */
    InitLigneCLK();
    InitCLK();
}

void MatriceLed::PinConfig() {
    DDRD |= (1<<DATA_PIN) | (1<<CLK_PIN) | (1<<STR_PIN);
    DDRC |= (1<<ALO) | (1<<AL1) | (1<<AL2) | (1<<CS1);
}

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

void GenerateBufferLed() {
    uint8_t masque = (1 << ligneInProcesse);
    for (uint8_t i=0; i<32; i++) {
        data_buffer[i] = (myMatrice.__MatriceLed[i] & masque) != masque; // Recupere le bit et l'inverse
    }
}

void ShowLigne() {
    /* Allume la ligne */

    /* Allume les colonne */

}

void MatriceLed::SetLed(uint8_t x, uint8_t y, bool state) {
    
}


void MatriceLed::Print(char str[], int8_t x) {
    /* Calcule la taille du tableau */
    uint8_t str_size = 0;
    while (str[str_size]!='\0') {
        str_size++;
    }

    /* Calcule la taille du tableau */
    uint8_t charactere[str_size*5 + str_size-1];

    /* Genere le tableau a partire du code ascii */
    for (uint8_t i=0; i<str_size; i++) {
        
    }

}

ISR(TIMER1_COMPA_vect) {
    /*Down la Clock*/
    PORTD &= ~(1<<CLK_PIN);

    /*Upload data*/
    PORTD |= (PORTD &~(1<<DATA_PIN)) | (data_buffer[data_index] << DATA_PIN);

    /*Incremente data_index*/
    data_index--;
}

ISR(TIMER1_COMPB_vect) {
    /*Up la clock*/
    PORTD |= (1<<CLK_PIN);

    /* Si on a finit les 32 bits on arrete l'a clk et data*/
    if (data_index <= 0) {
        TIMSK1 = 0; // Arrete les interuption sur TIMER1
    }
}

ISR(TIMER0_COMPA_vect) {
    /* Push les donnée sur les leds et affiche*/
    ShowLigne();

    /* Debut du travail sur la ligne suivante */
    ligneInProcesse = (ligneInProcesse+1)%8;

    /* Genere le buffer pour preparer le prochain affichage */
    GenerateBufferLed();

    /* Rallume les interuption Timer 1 */
    data_index = MATRICE_SIZE_X-1; // Remet data index a la valeur max
    TCNT1 = 0; // Remet a 0 le timer1 vant de le rallumer
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
}

