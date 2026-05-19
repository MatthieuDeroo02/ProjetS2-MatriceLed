#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

#define Masque_PD2 1<<3
#define Masque_PD3 1<<4


class clock {
public:
    void Begin();
    void Afficher_Heures();

    
    

private:
    void InitRTC();
    void InitPort();

    void UpdateRTC();

    void SetHeures();
    void SetDates();

    bool BP1_Appuyer();
    bool BP2_Appuyer();

    RTC_DS1307 TinyRtc;
    DateTime Times;

    typedef struct{
    int hour;
    int minute;
    int second;
    }T_Times;

    typedef struct{
        int day;
        int month;
        int year;
    }T_Dates;

    T_Times times;
    T_Dates dates;
};

