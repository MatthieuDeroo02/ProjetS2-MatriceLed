#include <Arduino.h>
#include "MatriceLed.hpp"
#include "Horloge.hpp"

int8_t x = 32; // Commence hors écran à droite

void setup() {
    myMatrice.begin();
    myMatrice.Clear();
}

void loop() {
    myMatrice.Clear();
    myMatrice.Print("HELLO", x);
    
    x--;
    
    // Remet à droite quand le texte est complètement sorti à gauche
    // 5 lettres * 6 pixels = 30 pixels de large
    if (x < -30) {
        x = 32;
    }
    
    delay(50); // Vitesse du défilement
}
