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
        250 Hz                              2 KHz                           64 KHz          Excellent camera OK
        500 Hz                              4 KHz                          128 KHz          Limite atteinte, charge CPU elevée
*/
#define MATRICE_DEFAULT_FREQUENCY 256
#define MATRICE_MAX_FREQUENCY 500
#define CLK_DEFAULT_FREQUENCY 200000
#define CLK_MAX_FREQUENCY 1000000
#define E9 1000000000 // 10^9


#define STATE 1
#define DEBUG 1


class MatriceLed{
public:
    MatriceLed(uint16_t matrice_frequency, uint16_t CLK_frequency);

    void begin(); // Initialise les ports
    void SetLed(uint8_t x, uint8_t y, bool state);
    void Show(); // Met a jour la matrice
    
protected:

private:
    void InitCLK();
    void SetCLK();
    void CLKState(bool state);
    void UploadLigne();
    uint8_t __MatriceLed[MATRICE_SIZE_X] = {0};

    uint32_t __MatriceUpdatePeriod_NS = E9/MATRICE_DEFAULT_FREQUENCY; 
    uint16_t __MatriceLigneUpdatePeriod_NS = (E9/MATRICE_DEFAULT_FREQUENCY)/8;
    uint16_t __CLKFrequency = MATRICE_DEFAULT_FREQUENCY*8*32;
};





int g_velo;
bool JeremStar(bool jerem){
    jerem = jerem || g_velo;
    return jerem;
}
int grenoble = 160;
void Chambery (int Destination, int distance, int temps){
    Destination = grenoble;
    distance = 180;
    temps = Destination * 2 + distance;
}