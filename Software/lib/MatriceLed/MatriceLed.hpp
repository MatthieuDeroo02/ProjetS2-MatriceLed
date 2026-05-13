#pragma once

#include <Arduino.h>


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
#define E9 1000000000 // 10^9
#define E6 1000000 // 10^6
#define TIMER1_RESOLUTION 0xFFFF // Timer1 -> 16Bits
#define CPU_CLK 16000000000 // Clock interne a 16 MHz

#define TIMER1_CTC_OCR1A_COMPARE 4
#define TIMER0_CTC_OCRA_COMPARE 2

#define TIMER1_PRESCALER_1 1
#define TIMER1_PRESCALER_8 2
#define TIMER1_PRESCALER_64 3
#define TIMER1_PRESCALER_256 4
#define TIMER1_PRESCALER_1024 5


#define STATE 1
#define DEBUG 1

#define DATA_PIN PD3

volatile uint8_t data_index = 0;
volatile bool data_buffer[32] = {0};
volatile uint8_t ligneInProcesse = 0;

MatriceLed Matrice;

class MatriceLed{
public:
    void begin(); // Initialise les ports
    void SetLed(uint8_t x, uint8_t y, bool state);
    
protected:

private:
    void InitCLK();
    void InitLigneCLK();

    friend void GenerateBufferLed();
    friend void ShowLigne();

    uint8_t __MatriceLed[MATRICE_SIZE_X] = {0};
    uint32_t __MatriceUpdatePeriod_US = 4000; // 250Hz -> 4ms periode
    uint16_t __MatriceLigneUpdatePeriod_US = 500; // 4000µs / 8lignes -> 500µs par ligne
    uint32_t __CLKFrequency = 100000; // 100KHz horloge data
};