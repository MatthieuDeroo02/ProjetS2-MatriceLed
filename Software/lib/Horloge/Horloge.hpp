#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

class clock {
public:
    void Begin();

    
    

private:
    void InitRTC();
    void UpdateRTC();
    void SetHeures();
    void SetDates();

    RTC_DS1307 TinyRtc;
    DateTime Time;

    typedef struct T_Heures {
    int hour;
    int minute;
    int second;
    };

    typedef struct T_Dates {
        int day;
        int month;
        int year;
    };

    T_Heures time;
    T_Dates date;
};

