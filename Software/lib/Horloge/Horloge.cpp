#include "Horloge.hpp"

#include<MatriceLed.hpp>
#include<Wire.h>
#include"RTClib.h"

//SDA -> PC4
//SCL -> PC5
//BP1 -> PD2
//BP2 -> PD3


/*-----Initialisation des modules I2C---------*/
void clock::InitRTC(){
    Wire.begin();
    TinyRtc.begin();
}
void clock::InitPort(){
    DDRD |= Masque_PD3 |Masque_PD2;
}


/*------Update Heure---------*/
void clock::UpdateRTC(){
    TinyRtc.now();
}

/*------Set Heures---------*/
void clock::SetHeures(){
    times.hour = Times.hour();
    times.minute = Times.minute();
    times.second = Times.second();
}

/*------Set Dates---------*/
void clock::SetDates(){
    dates.day = Times.day();
    dates.month = Times.month();
    dates.year = Times.year();
}


void clock::Afficher_Heures(){
    if(BP1_Appuyer()){
        UpdateRTC();
        SetHeures();

    }
}

/*------BP---------*/
bool clock::BP1_Appuyer(){
    if(PORTD &= Masque_PD2){
        return true;
    }
    return false;
}
bool clock::BP2_Appuyer(){
        if(PORTD &= Masque_PD3){
        return true;
    }
    return false;
}