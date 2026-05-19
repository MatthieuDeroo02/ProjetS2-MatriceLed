#ifndef _HORLOGE_LED_
#define _HORLOGE_LED_

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

#define BP1 PD2 
#define BP2 PD3
#define SDA PC4
#define SCL PC5

#define SERIAL_MONITOR_BAUD 9600

#define DEBUG 0

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

extern clock myClock;

#endif