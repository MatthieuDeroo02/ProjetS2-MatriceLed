#ifndef _MATRICE_LED_
#define _MATRICE_LED_

#include <Arduino.h>
#include "asciiLed.hpp"

/* Matrice LED dimension ( *=LED )

0   1   2   3       31
*   *   *   *       *   0
*   *   *   *       *   1

*   *   *   *       *   7

*/
#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8


/* Frequence de rafrechissement du tableau
Frequence rafrechissement matrice | frequence rafrechissement ligne | frequence CLK min | Result
        50 Hz                               400 Hz                          12,8 KHz        Scintillement visible
        80 Hz                               640 Hz                          20,48 KHz       Limite acceptable
        125 Hz                              1 KHz                           32 KHz          Recommandé (Scintillement camera)
        250 Hz                              2 KHz                           64 KHz          Excellent camera OK                     ----> This is the developement object
        500 Hz                              4 KHz                          128 KHz          Limite atteinte, charge CPU elevée
*/
#define MATRICE_DEFAULT_FREQUENCY 250
#define MATRICE_MAX_FREQUENCY 500
#define CLK_DEFAULT_FREQUENCY 200000
#define CLK_MAX_FREQUENCY 1000000
#define TIMER1_RESOLUTION 0xFFFF // Timer1 -> 16Bits
#define CPU_CLK 16000000000 // Clock interne a 16 MHz

#define TIMER1_CTC_OCR1A_COMPARE 4
#define TIMER0_CTC_OCRA_COMPARE 2

#define TIMER1_PRESCALER_1 1
#define TIMER1_PRESCALER_8 2
#define TIMER1_PRESCALER_64 3
#define TIMER1_PRESCALER_256 4
#define TIMER1_PRESCALER_1024 5

#define E9 1000000000 // 10^9
#define E6 1000000 // 10^6
#define E3 1000 // 10^3

#define STATE 1
#define DEBUG_LED 0

#define OFF 0
#define ON 1

#define DATA_PIN PD5
#define CLK_PIN PD6
#define STR_PIN PD4
#define ALO_PIN PC0
#define AL1_PIN PC1
#define AL2_PIN PC2
#define CS1_PIN PC3

#define DATA_PIN PD5
#define CLK_PIN PD6
#define STR_PIN PD4
#define ALO_PIN PC0
#define AL1_PIN PC1
#define AL2_PIN PC2
#define CS1_PIN PC3

#define BIT0 0
#define BIT1 1
#define BIT2 2
#define BIT3 3
#define BIT4 4
#define BIT5 5
#define BIT6 6
#define BIT7 7


extern volatile int8_t data_index ;
extern volatile bool data_buffer[32];
extern volatile uint8_t ligneInProcesse;

extern volatile uint32_t nbr_debordement;

void GenerateBufferLed();
void ShowLigne();

class MatriceLed{
public:
    void begin(); // Initialise les port
    void SetLed(uint8_t x, uint8_t y, bool state);

    void Print(char str[], int8_t x, uint8_t x_min = 0, uint8_t x_max = MATRICE_SIZE_X-1);
    void Print(const char str[], int8_t x, uint8_t x_min = 0, uint8_t x_max = MATRICE_SIZE_X-1);
    void Print(char charactere, int8_t x, uint8_t x_min = 0, uint8_t x_max = MATRICE_SIZE_X-1);

    void Clear();
    void ClearZone(uint8_t x_min, uint8_t x_max);
    void AllOn();
    unsigned long millis();

#ifdef _HORLOGE_
    void PrintTime(clock& myClock);
#endif
    
    
private:
    void InitCLK();
    void InitLigneCLK();
    void PinConfig();

    friend void GenerateBufferLed();
    friend void ShowLigne();

    uint8_t __MatriceLed[MATRICE_SIZE_X] = {0xFF}; //FF for debug
    uint32_t __MatriceUpdatePeriod_US = 4000; // 250Hz -> 4ms periode
    uint16_t __MatriceLigneUpdatePeriod_US = 500; // 4000µs / 8lignes -> 500µs par ligne
    uint32_t __CLKFrequency = 100000; // 100KHz horloge data
};

extern MatriceLed myMatrice;

#endif