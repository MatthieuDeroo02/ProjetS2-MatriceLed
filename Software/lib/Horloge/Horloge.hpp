#ifndef _HORLOGE_LED_
#define _HORLOGE_LED_

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

#define BP1 PD2 
#define BP2 PD3
#define SDA PC4
#define SCL PC5

#define YEAR 2026
#define MONTH 5
#define DAY 20
#define HOUR 6
#define MINUTE 30
#define SECOND 30
#define DAY_OF_WEEK 3

#define SERIAL_MONITOR_BAUD 9600

#define DEBUG_LED 1

#define Masque_PD2 1<<2
#define Masque_PD3 1<<3

class clock {
public:
    void Begin();

    void Updates_Heures();
    void Updates_Dates();

    void Init_Heures();

private:
    void InitPort();

    void UpdateRTC();

    void SetHeures();
    void SetDates();

    bool BP1_Appuyer();
    bool BP2_Appuyer();

    RTC_DS1307 TinyRtc;
    DateTime Times;

    typedef struct{
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    }T_Times;

    typedef struct{
        uint8_t day;
        uint8_t month;
        uint16_t year;
    }T_Dates;

    T_Times times;
    T_Dates dates;


    typedef struct{
        uint16_t year = YEAR;
        uint8_t month = MONTH;
        uint8_t day = DAY;
        uint8_t hour = HOUR;
        uint8_t minute = MINUTE;
        uint8_t second = SECOND;
        uint8_t dayOfWeek = DAY_OF_WEEK;
    }TAdjust;

    TAdjust adjust;
};

extern clock myClock;

#endif