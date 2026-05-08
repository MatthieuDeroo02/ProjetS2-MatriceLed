#pragma once

#include <Arduino.h>

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8

#define STATE 1


class MatriceLed{
public:
    void begin(); // Initialise les ports
    void SetLed(uint8_t x, uint8_t y, bool state);
    void Show(); // Met a jour la matrice
    
protected:

private:
    void SetCLK();
    void CLKState(bool state);
    void UploadLigne();
    uint8_t __MatriceLed[MATRICE_SIZE_X] = {0};
};