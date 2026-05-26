#include "MatriceLed.hpp"

volatile int8_t data_index = 0;
volatile bool data_buffer[32] = {1};
volatile uint8_t ligneInProcesse = 0;

volatile uint32_t nbr_debordement = 0;

MatriceLed myMatrice;
snake mySnake;

#if DEBUG_LED
    volatile bool debug_data_buffer[32];
#endif

void MatriceLed::begin(){

#if DEBUG_LED
    Serial.begin(9600);
#endif

    /* Initilaise les Pin GPIO */
    PinConfig();

    /* Initilaise les differentes clock */
    InitLigneCLK();
    InitCLK();

    /* Allume la matrice */
    PORTC |= (1<<CS1_PIN);

    /* Met toute les led allumer 0 */
    Clear();
}

void MatriceLed::PinConfig() {
    DDRD |= (1<<DATA_PIN) | (1<<CLK_PIN) | (1<<STR_PIN);
    DDRC |= (1<<ALO_PIN) | (1<<AL1_PIN) | (1<<AL2_PIN) | (1<<CS1_PIN);
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
    //TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);

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
    //uint8_t masque = (1 << ligneInProcesse);
    for (uint8_t i=0; i<32; i++) {
        if(mySnake.__SnakeBuffer){
            //mySnake.__MatriceLed[i] = ((myMatrice.__MatriceLed[i] >> ligneInProcesse) & 1) ^ 1;
        }
        else{
            data_buffer[i] = ((myMatrice.__MatriceLed[i] >> ligneInProcesse) & 1) ^ 1; // Recupere le bit et l'inverse
        }
    }
#if DEBUG_LED
    for (int i = 0; i<32; i++) {
        Serial.print(data_buffer[i]);
    }
    Serial.println();
#endif

}

void ShowLigne() {
    /* Etteint la matrice */
    PORTC &= ~(1<<CS1_PIN);

    /* Envoie la ligne */
    PORTC = (PORTC &~(1<<ALO_PIN)) | (((ligneInProcesse >> BIT0) & 1) << ALO_PIN);
    PORTC = (PORTC &~(1<<AL1_PIN)) | (((ligneInProcesse >> BIT1) & 1) << AL1_PIN);
    PORTC = (PORTC &~(1<<AL2_PIN)) | (((ligneInProcesse >> BIT2) & 1) << AL2_PIN);

#if DEBUG_LED
    Serial.print("lp: ");
    Serial.print(ligneInProcesse);
    Serial.print("  |   AL: ");
    Serial.println(PORTC & ((1<<ALO_PIN) | (1<<AL1_PIN) | (1<<AL2_PIN)));
#endif

    /* Envoi les colonne */
    PORTD |= (1<<STR_PIN);

    /* Remmet a Zero STR pour pas que les valeur nouvelle partubent */
    PORTD &= ~(1<<STR_PIN);

    /* Rallume la matrice */
    PORTC |= (1<<CS1_PIN);
}

void MatriceLed::SetLed(uint8_t x, uint8_t y, bool state) {
    myMatrice.__MatriceLed[x] = (myMatrice.__MatriceLed[x] & ~(1<<y)) | (state << y);
}

void MatriceLed::Print(char charactere, int8_t x, uint8_t x_min, uint8_t x_max) {
    for (uint8_t i=0; i<5; i++) {
        if (x >= x_min && x <= x_max) {
            __MatriceLed[x] = font5x8[charactere - 32][i];
        }
        x++;
    }
}

void MatriceLed::Print(char str[], int8_t x, uint8_t x_min, uint8_t x_max) {

    /* Tant que c'est pas le caractere null on affiche le prochain caractere */
    uint8_t str_size = 0;
    while (str[str_size]!='\0') {
        Print(str[str_size], x, x_min, x_max);
        x+=6;
        str_size++;
    }
}

void MatriceLed::Print(const char str[], int8_t x, uint8_t x_min, uint8_t x_max) {
    /* Tant que c'est pas le caractere null on affiche le prochain caractere */
    uint8_t str_size = 0;
    while (str[str_size]!='\0') {
        Print(str[str_size], x, x_min, x_max);
        x+=6;
        str_size++;
    }
}

void MatriceLed::Clear() {
    for (int i=0; i<32; i++) {
        __MatriceLed[i] = 0; 
    }
}

void MatriceLed::ClearZone(uint8_t x_min, uint8_t x_max) {
    for (int i=x_min; i<= x_max; i++) {
        __MatriceLed[i] = 0; 
    }
}

void MatriceLed::AllOn() {
    for (int i=0; i<32; i++) {
        __MatriceLed[i] = 0xFF; 
    }
}

unsigned long MatriceLed::millis() {
    return (nbr_debordement * 124UL + TCNT0) * 4UL / 1000UL;
}

ISR(TIMER1_COMPA_vect) {
    /*Down la Clock*/
    PORTD &= ~(1<<CLK_PIN);

    /*Upload data*/
    PORTD = (PORTD & ~(1<<DATA_PIN)) | (data_buffer[data_index] << DATA_PIN);

#if DEBUG_LED
    debug_data_buffer[data_index] = (((PIND)>>DATA_PIN) & 1);
#endif

    /*Incremente data_index*/
    data_index--;
}

ISR(TIMER1_COMPB_vect) {
    /*Up la clock*/
    PORTD |= (1<<CLK_PIN);

    /* Si on a finit les 32 bits on arrete l'a clk et data*/
    if (data_index < 0) {
        TIMSK1 = 0; // Arrete les interuption sur TIMER1
        //PORTD &= ~(1<<DATA_PIN);
#if DEBUG_LED
        Serial.print("Fin de transmition: ");
        for (int i=0; i<32; i++) {
            Serial.print(debug_data_buffer[i]);
        } Serial.println();
#endif
    }
}

ISR(TIMER0_COMPA_vect) {
    if (TIMSK1 != 0) return; // Pas encore fini → on skip ce cycle

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
    //PORTD |= (1<<DATA_PIN);

    /* Rajoute un debordement pour la fonction millis */
    nbr_debordement++;
}

