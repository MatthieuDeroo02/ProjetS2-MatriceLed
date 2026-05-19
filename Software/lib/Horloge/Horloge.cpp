#include "Horloge.hpp"
#include <MatriceLed.hpp>
#include <Wire.h>
#include "RTClib.h"

clock myClock;

void clock::Begin(){
    #if DEBUG
        Serial.begin(SERIAL_MONITOR_BAUD);
    #endif
        /*---Initialisation liaison I2C---*/
        Wire.begin();

        /*---Initialisation module Tiny RTC---*/
        TinyRtc.begin();

        /*---Initialisation Port BP---*/
        InitPort();
}


/*-----Initialisation des modules I2C---------*/
void clock::InitPort(){
    DDRD |= Masque_PD3 |Masque_PD2;
    PORTD |= Masque_PD2 | Masque_PD3;
}




void clock::Updates_Heures(){
    if(BP1_Appuyer()){
        /*---Updates heures+dates---*/
        UpdateRTC();

        /*---Enregistrement Heures---*/
        SetHeures();

        #if DEBUG
            Serial.print("Heure:"); 
            Serial.println(times.hour);
            Serial.print("Minutes:"); 
            Serial.println(times.minute);
            Serial.print("Secondes:"); 
            Serial.println(times.second);
        #endif
    }
}

void clock::Updates_Dates(){
    if(BP2_Appuyer()){
        /*---Updates heures+dates---*/
        UpdateRTC();

        /*---Enregistrement Dates---*/
        SetDates();
        
        #if DEBUG
            Serial.print("Day:"); 
            Serial.println(dates.day);
            Serial.print("Month:"); 
            Serial.println(dates.month);
            Serial.print("Year:"); 
            Serial.println(dates.year);
        #endif
    }
}


/*------Update Heure---------*/
void clock::UpdateRTC(){
    TinyRtc.now();
}

void clock::SetHeures(){
    times.hour = Times.hour();
    times.minute = Times.minute();
    times.second = Times.second();
}

void clock::SetDates(){
    dates.day = Times.day();
    dates.month = Times.month();
    dates.year = Times.year();
}








/*------BP---------*/
bool clock::BP1_Appuyer(){
    if((PIND & Masque_PD2) == 1){
        #if DEBUG
            Serial.println("BP1 Appuyer");
        #endif
        return true;
    }
    else{
        return false;
    }
}

bool clock::BP2_Appuyer(){
    if((PIND & Masque_PD3) == 1){
        #if DEBUG
            Serial.println("BP2 Appuyer");
        #endif
        return true;
    }
    else{
        return false;
    }
}