#ifndef _RTC_EEPROM_HPP_
#define _RTC_EEPROM_HPP_

#include <Arduino.h>
#include <Wire.h>
#include "MatriceLed.hpp"

#define RTC_EEPROM_I2C_ADDR 0x50

class RTC_memoire{
public:
    void Begin(byte addr = RTC_EEPROM_I2C_ADDR);

    void Write(byte* data, uint8_t size, uint16_t memAddr);
    void WriteByte(uint16_t memAddr, byte data);
    
    bool Read(uint16_t memAddr, uint8_t size, byte* data);
    byte ReadByte(uint16_t memAddr, bool *error);

private:
    byte __Eeprom_addr;
    unsigned long __write_delay = 0;
};

#endif