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

/*------Update Heure---------*/
void clock::UpdateRTC(){
    TinyRtc.now();
}

/*------Set Heures---------*/
void clock::SetHeures(){
    time.hour = Time.hour();
    time.minute = Time.minute();
    time.second = Time.second();
}

/*------Set Dates---------*/
void clock::SetDates(){
    date.day = Time.day();
    date.month = Time.month();
    date.year = Time.year();
}