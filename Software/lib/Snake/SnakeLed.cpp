#include "SnakeLed.hpp"

void snake::InitSnake(){
    for(int i=0; i<MATRICE_SIZE_X; i++) {
        for (int j=0; j<MATRICE_SIZE_Y; j++) {
            __MatriceLed[i][j] = 0;
        }
    }
}