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


uint16_t EEMEM minHumidity = DEFAULT_MINHUMODITY;
uint16_t EEMEM maxHumidity = DEFAULT_MAXHUMODITY;
uint16_t EEMEM minPumpOnTime = DEFAULT_PUMPTIME;
uint16_t EEMEM waitTimeAfterpump = DEFAULT_AFTERPUMPTIME;

uint8_t EEMEM polivMode = DEFAULT_MODE;

}



uint16_t PolivSettings::getWaitTimeAfterpump() const
{
    return eeprom_read_word(&backstagemem::waitTimeAfterpump);
}

void PolivSettings::setWaitTimeAfterpump(const uint16_t & value)
{
    eeprom_write_word(&backstagemem::waitTimeAfterpump, value);
}

DeviceMode PolivSettings::getMode()
{
    return (DeviceMode)eeprom_read_byte(&backstagemem::polivMode);
}

void PolivSettings::setMode(DeviceMode mode)
{
    eeprom_write_byte(&backstagemem::polivMode, (uint8_t)mode);
}

uint8_t PolivSettings::getMinHumidity(uint8_t pos) const
{
    static uint16_t tmp = 0;
    if(pos == 0)
        tmp = eeprom_read_word(&backstagemem::minHumidity);
    return (uint8_t)((tmp >> 8 * pos) & 0xff);

}

void PolivSettings::setMinHumidity(uint8_t value, uint8_t pos)
{
    static uint16_t tmp = 0;
    ((uint8_t *) * (&tmp))[pos] = value;
    if(pos == 1) {
        eeprom_write_word(&backstagemem::minHumidity, tmp);
        tmp = 0;
    }
}

uint8_t PolivSettings::getMaxHumidity(uint8_t pos) const
{
    static uint16_t tmp = 0;
    if(pos == 0)
        tmp = eeprom_read_word(&backstagemem::maxHumidity);
    return (uint8_t)((tmp >> 8 * pos) & 0xff);
}

void PolivSettings::setMaxHumidity(uint8_t value, uint8_t pos)
{
    static uint16_t tmp = 0;
    ((uint8_t *) * (&tmp))[pos] = value;
    if(pos == 1) {
        eeprom_write_word(&backstagemem::maxHumidity, tmp);
        tmp = 0;
    }
}

uint8_t PolivSettings::getMinPumpOnTime(uint8_t pos) const
{
    static uint16_t tmp = 0;
    if(pos == 0)
        tmp = eeprom_read_word(&backstagemem::minPumpOnTime);
    return (uint8_t)((tmp >> 8 * pos) & 0xff);
}

void PolivSettings::setMinPumpOnTime(uint8_t value, uint8_t pos)
{
    static uint16_t tmp = 0;
    ((uint8_t *) * (&tmp))[pos] = value;
    if(pos == 1) {
        eeprom_write_word(&backstagemem::minPumpOnTime, tmp);
        tmp = 0;
    }
}

uint8_t PolivSettings::getWaitTimeAfterpump(uint8_t pos) const
{
    static uint16_t tmp = 0;
    if(pos == 0)
        tmp = eeprom_read_word(&backstagemem::waitTimeAfterpump);
    return (uint8_t)((tmp >> 8 * pos) & 0xff);
}

void PolivSettings::setWaitTimeAfterpump(uint8_t value, uint8_t pos)
{
    static uint16_t tmp = 0;
    ((uint8_t *) * (&tmp))[pos] = value;
    if(pos == 1) {
        eeprom_write_word(&backstagemem::waitTimeAfterpump, tmp);
        tmp = 0;
    }
}

uint8_t PolivSettings::getMode() const
{
    return eeprom_read_byte(&backstagemem::polivMode);
}

void PolivSettings::setMode(uint8_t mode)
{
    eeprom_write_byte(&backstagemem::polivMode, mode);
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

void PolivSettings::setAddress(uint8_t addr)
{
    eeprom_write_byte(&backstagemem::slaveAddress, addr);
}

uint8_t PolivSettings::getAddress() const
{
    return eeprom_read_byte(&backstagemem::slaveAddress);
}

uint8_t PolivSettings::getDeviceGUID(uint8_t pos) const
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
