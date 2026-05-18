#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"


typedef struct{
    int hour;
    int minute;
    int second;
}THeures;

typedef struct{
    int day;
    int month;
    int year;
}TDates;

THeures g_heures;
TDates g_dates;

class clock {
public:
    

private:

}

