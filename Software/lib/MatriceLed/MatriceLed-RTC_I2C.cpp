#include<MatriceLed.hpp>
#include<Wire.h>
#include"RTClib.h"

//SDA -> PC4
//SCL -> PC5
//BP1 -> PD2
//BP2 -> PD3

RTC_DS1307 TinyRtc;

DateTime Time;

/*-----Initialisation des modules I2C---------*/
void MatriceLed::InitRTC(){
    Wire.begin();
    TinyRtc.begin();
}

/*------Update Heure---------*/
void MatriceLed::UpdateRTC(){
    TinyRtc.now();
}

THeures SetHeures(){
    g_heures.hour = Time.hour();
    g_heures.minute = Time.minute();
    g_heures.second = Time.second();
}

TDates SetDates(){
    g_dates.day = Time.day();
    g_dates.month = Time.month();
    g_dates.year = Time.year();
}





