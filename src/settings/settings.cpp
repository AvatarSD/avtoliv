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
uint8_t EEMEM deviceName[DEVNAME_SIZE] = DEV_NAME;
uint16_t EEMEM deviceHWver = DEV_HW_VER;
const uint16_t deviceSWver = DEV_SW_VER;


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

uint8_t PolivSettings::getHumidity(uint8_t pos) const
{

}

void PolivSettings::setHumidity(uint8_t value, uint8_t pos)
{

}

uint8_t PolivSettings::getMinHumidity(uint8_t pos) const
{

}

void PolivSettings::setMinHumidity(uint8_t value, uint8_t pos)
{

}

uint8_t PolivSettings::getMaxHumidity(uint8_t pos) const
{

}

void PolivSettings::setMaxHumidity(uint8_t value, uint8_t pos)
{

}

uint8_t PolivSettings::getMinPumpOnTime(uint8_t pos) const
{

}

void PolivSettings::setMinPumpOnTime(uint8_t value, uint8_t pos)
{

}

uint8_t PolivSettings::getWaitTimeAfterpump(uint8_t pos) const
{

}

void PolivSettings::setWaitTimeAfterpump(uint8_t value, uint8_t pos)
{

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

uint8_t PolivSettings::getI2cAddress() const
{
    return eeprom_read_byte(&backstagemem::slaveAddress);
}

uint8_t PolivSettings::getGUID(uint8_t pos) const
{
    return eeprom_read_byte(&backstagemem::GUID[pos]);
}

uint8_t PolivSettings::getDeviceName(uint8_t pos) const
{
    return eeprom_read_byte(&backstagemem::deviceName[pos]);
}

uint8_t PolivSettings::getDeviceSWver(uint8_t pos) const
{
    return *(((uint8_t *) &backstagemem::deviceSWver) + pos);
}

uint8_t PolivSettings::getDeviceHWver(uint8_t pos) const
{
    return eeprom_read_byte(((uint8_t *)&backstagemem::deviceHWver) + pos);
}
