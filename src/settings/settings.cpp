#include "settings.h"
#include <avr/eeprom.h>


namespace backstagemem
{

uint8_t EEMEM GUID[GUID_SIZE] = { // TODO autogen guid
    0x66, 0x11, 0x70, 0x8B,
    0xC4, 0x76, 0x41, 0x96,
    0x91, 0x12, 0xA0, 0x91,
    0x44, 0xF0, 0xBF, 0x9C
};

uint8_t EEMEM slaveAddress = I2C_SLAVE_ADDRESS;


uint16_t EEMEM minHumidity = 350;
uint16_t EEMEM maxHumidity = 700;
uint16_t EEMEM minPumpOnTime = 4;
uint16_t EEMEM waitTimeAfterpump = 120;

}



uint16_t PolivSettings::getWaitTimeAfterpump() const
{
    return eeprom_read_word(&backstagemem::waitTimeAfterpump);
}

void PolivSettings::setWaitTimeAfterpump(const uint16_t & value)
{
    eeprom_write_word(&backstagemem::waitTimeAfterpump, value);
}

uint16_t PolivSettings::getMinPumpOnTime() const
{
    return eeprom_read_word(&backstagemem::minPumpOnTime);
}

void PolivSettings::setMinPumpOnTime(const uint16_t & value)
{
    eeprom_write_word(&backstagemem::minPumpOnTime , value);
}

uint16_t PolivSettings::getMaxHumidity() const
{
    return eeprom_read_word(&backstagemem::maxHumidity);
}

void PolivSettings::setMaxHumidity(const uint16_t & value)
{
    eeprom_write_word(&backstagemem::maxHumidity , value);
}

uint16_t PolivSettings::getMinHumidity() const
{
    return eeprom_read_word(&backstagemem::minHumidity);
}

void PolivSettings::setMinHumidity(const uint16_t & value)
{
    eeprom_write_word(&backstagemem::minHumidity, value);
}

void PolivSettings::setI2cAddress(uint8_t addr)
{
    eeprom_write_byte(&backstagemem::slaveAddress, addr);
}

uint8_t PolivSettings::getI2cAddress()
{
    return eeprom_read_byte(&backstagemem::slaveAddress);
}

uint8_t PolivSettings::getGUID(uint8_t pos)
{
    return eeprom_read_byte(&backstagemem::GUID[pos]);
}
