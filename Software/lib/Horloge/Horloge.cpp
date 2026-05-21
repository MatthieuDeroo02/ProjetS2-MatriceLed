#include "Horloge.hpp"
#include <MatriceLed.hpp>
#include <Wire.h>
#include "RTClib.h"

clock myClock;

void clock::Begin(){
    #if DEBUG_HORLOGE
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
    //PORTD |= Masque_PD2 | Masque_PD3; -> serve pas ici car on utilise le pull-down
}





void clock::Updates_Heures(){
    /*---Updates heures+dates---*/
    UpdateRTC();

    /*---Enregistrement Heures---*/
    SetHeures();

    if(BP1_Appuyer()){
        #if DEBUG_HORLOGE
            Serial.print("Heure:"); 
            Serial.println(times.hour);
            Serial.print("Minutes:"); 
            Serial.println(times.minute);
            Serial.print("Secondes:"); 
            Serial.println(times.second);
        #endif
    }

    times.hour = ConvNumAscii(times.hour);
    myMatrice.Print(times.hour, 2);
    //myMatrice.Print(" : \0", 2);
    //myMatrice.Print(times.minute, 2);
}

void clock::Updates_Dates(){
    /*---Updates heures+dates---*/
    UpdateRTC();

    /*---Enregistrement Dates---*/
    SetDates();

    if(BP2_Appuyer()){
        #if DEBUG_HORLOGE
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
    TinyRtc.now(); // Update les heures et les dates dans le module RTC
}

void clock::SetHeures(){
    times.hour = Times.hour(); // Update les heures
    times.minute = Times.minute(); // Update les minutes
    times.second = Times.second(); // Update les secondes
}

void clock::SetDates(){
    dates.day = Times.day(); // Uopdate les jours
    dates.month = Times.month(); // Update les mois
    dates.year = Times.year(); // Update les années
}

/*------BP---------*/
bool clock::BP1_Appuyer(){
    if((PIND & Masque_PD2) != 0){
        #if DEBUG_HORLOGE
            Serial.println("BP1 Appuyer");
        #endif
        return true; // BP1 Appuyer
    }
    else{
        return false; // BP1 Non Appuyer
    }
}

bool clock::BP2_Appuyer(){
    if((PIND & Masque_PD3) != 0){
        #if DEBUG_HORLOGE
            Serial.println("BP2 Appuyer");
        #endif
        return true; // BP2 Appuyer
    }
    else{
        return false; // BP2 Non Appuyer
    }
}





void clock::Init_Heures(){
    #if DEBUG_HORLOGE
        Serial.println("Init heure");
        TinyRtc.adjust(DateTime(2000, 1, 1, 0, 0, 0));
    #endif

    /*---Ecrit l'heure dans le module RTC---*/
    TinyRtc.adjust(DateTime(
        adjust.year, // Envoye l'année
        adjust.month, // Envoye le mois
        adjust.day, // Envoye le jour
        adjust.hour, // Envoye l'heure
        adjust.minute, // Envoye les minutes
        adjust.second // Envoye les secondes
        //adjust.dayOfWeek
    ));
}


uint8_t clock::ConvNumAscii(uint8_t num){
    #if DEBUG_HORLOGE
        if(num > 9){
            Serial.println("ERREUR Conversion\n");
        }
    #endif
    return num +48;
}

T_Times clock::GetTime() {
    return times;
}