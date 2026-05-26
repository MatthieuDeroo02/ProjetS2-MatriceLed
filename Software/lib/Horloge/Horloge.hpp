#ifndef _HORLOGE_
#define _HORLOGE_

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

#define BP1 PD2 
#define BP2 PD3
#define SDA PC4 // I2C
#define SCL PC5 // I2C

#define SERIAL_MONITOR_BAUD 9600

#define DEBUG_HORLOGE 1

#define Masque_PD2 1<<2
#define Masque_PD3 1<<3

class clock {
public:
    void Begin();
    void Begin(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,  uint8_t second);
    void UpdateRTC();

    uint16_t GetYear()  { return time.year();   };
    uint8_t GetMouth()  { return time.month();  };
    uint8_t GetDay()    { return time.day();    };
    uint8_t GetHour()   { return time.hour();   };
    uint8_t GetMinute() { return time.minute(); };
    uint8_t GetSecond() { return time.second(); };
    
private:

    DateTime time;
    RTC_DS1307 TinyRtc;
};

uint16_t ConvChiffreAscii(uint8_t num);

#endif