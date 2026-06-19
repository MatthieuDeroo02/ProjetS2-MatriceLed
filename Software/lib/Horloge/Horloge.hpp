#ifndef _HORLOGE_
#define _HORLOGE_

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
//#include "MatriceLed.hpp"

#define SDA PC4 // I2C
#define SCL PC5 // I2C

#define SERIAL_MONITOR_BAUD 9600

#define DEBUG_HORLOGE 0

class clock {
public:
    /**
     * @brief Initialise la liaison I2C avec le module RTC
     */
    void Begin();

    /**
     * @param year
     * @param mouth
     * @param day
     * @param hour
     * @param minute
     * @param second
     * @brief Initialise la liaison I2C avec le module RTC et met a jour la date et l'heure dans le module RTC 
     */
    void Begin(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,  uint8_t second);

    /**
     * @brief requupert l'heure du module RTC et à jour la variable time
     */
    void UpdateRTC();

    /**
     * @brief Donne la valeur de l'element specifier
     */
    uint16_t GetYear()  { return time.year();   };
    uint8_t GetMouth()  { return time.month();  };
    uint8_t GetDay()    { return time.day();    };
    uint8_t GetHour()   { return time.hour();   };
    uint8_t GetMinute() { return time.minute(); };
    uint8_t GetSecond() { return time.second(); };

//#ifdef _MATRICE_LED_
    /**
     * @brief fonction haut niveau qui recupere l'heure et l'affiche directement sur la matrice Led
     */
    void PrintTimeOnMatrice();
//#endif
    
private:

    DateTime time;
    RTC_DS1307 TinyRtc;
};


/**
 * @param num chiffre a convertir en charactere
 * @return character corespondant au chiffre
 * @brief Converti un chiffre en son character dans le code ASCII pour l'utiliser dans la fonction Print de la matrice
 */
char ConvChiffreAscii(uint8_t num);


#endif