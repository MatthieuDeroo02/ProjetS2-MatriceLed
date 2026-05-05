#pragma once

#include <Arduino.h>

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8


class MatriceLed{
public:
    void begin(); // Initialise les ports
    void SetLed();
    void Show(); // Met a jour la matrice
private:
    uint8_t __MatriceLed[MATRICE_SIZE_X];
};