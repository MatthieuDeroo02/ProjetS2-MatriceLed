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
    InitPort();
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
    InitRTC();
    if(BP1_Appuyer()){
        UpdateRTC();
        SetHeures();
        Serial.println(times.hour);
    }
}

/*------BP---------*/
bool clock::BP1_Appuyer(){
    if((PIND & Masque_PD2) == 0){
        Serial.println("BP1");
        return true;
    }
    else{
        return false;
    }
}
bool clock::BP2_Appuyer(){
        if((PIND & Masque_PD3) == 0){
            Serial.println("BP2");
            return true;
    }
    else{
        return false;
    }
}