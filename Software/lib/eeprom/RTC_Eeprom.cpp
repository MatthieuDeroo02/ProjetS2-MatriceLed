#include "RTC_Eeprom.hpp"

void RTC_memoire::Begin(byte addr) {
    __Eeprom_addr = addr;
    Wire.begin();
    __write_delay = 0;
}

void RTC_memoire::WriteByte(uint16_t memAddr, byte data) {
    while (newMillis()-__write_delay <= 5) {} //Delai d'ecriture pour le module

    Wire.beginTransmission(__Eeprom_addr);
    Wire.write((memAddr >> 8) & 0xFF);
    Wire.write(memAddr & 0xFF);

    Wire.write(data);

    Wire.endTransmission();
    __write_delay = newMillis();
}

void RTC_memoire::Write(byte* data, uint8_t size, uint16_t memAddr) {
    for (uint16_t i = 0; i < size; i++) {
        WriteByte(memAddr+i, data[i]);
    }
}

byte RTC_memoire::ReadByte(uint16_t memAddr, bool* error) {
    while (newMillis()-__write_delay <= 5) {} //Delai d'ecriture pour le module
    Wire.beginTransmission(__Eeprom_addr);
    Wire.write((memAddr >> 8) & 0xFF);
    Wire.write(memAddr & 0xFF);
    Wire.endTransmission();

    Wire.requestFrom(__Eeprom_addr, 1);
    if (Wire.available()) {
        *error = false;
        return Wire.read(); //No ERROR
    } 
    *error = true;
    return 0; //ERROR
}

bool RTC_memoire::Read(uint16_t memAddr, uint8_t size, byte* data) {
    bool error;
    for (uint8_t i=0; i<size; i++) {
        data[i] = ReadByte(memAddr, &error);
        if (error == true) break;
    }
    return error;
}