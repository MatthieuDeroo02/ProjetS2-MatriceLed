#ifndef _RTC_EEPROM_HPP_
#define _RTC_EEPROM_HPP_

#include <Arduino.h>
#include <Wire.h>
#include "MatriceLed.hpp"

#define RTC_EEPROM_I2C_ADDR 0x57

class RTC_memoire{
public:
    void Begin(byte addr = RTC_EEPROM_I2C_ADDR);

    void Write(byte* data, uint8_t size, uint16_t memAddr);
    void WriteByte(uint16_t memAddr, byte data);
    
    byte* Read(uint16_t memAddr, uint8_t size, bool* error);
    byte ReadByte(uint16_t memAddr, bool *error);

private:
    byte __Eeprom_addr;
};

#endif