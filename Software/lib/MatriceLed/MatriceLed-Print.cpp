#include "MatriceLed.hpp"

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