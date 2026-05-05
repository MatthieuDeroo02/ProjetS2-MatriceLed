#pragma once

#include <Arduino.h>

#define MATRICE_SIZE_X 32
#define MATRICE_SIZE_Y 8


class MatriceLed{
public:
    void begin();
    void SetLed();
    void Show();
private:
    uint8_t __MatriceLed[MATRICE_SIZE_X];
};