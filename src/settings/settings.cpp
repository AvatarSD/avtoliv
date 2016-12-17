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

HumidityVal EEMEM minHumidity = DEFAULT_MINHUMODITY;
HumidityVal EEMEM maxHumidity = DEFAULT_MAXHUMODITY;
TimeSecVal EEMEM minPumpOnTime = DEFAULT_PUMPTIME;
TimeSecVal EEMEM waitTimeAfterpump = DEFAULT_AFTERPUMPTIME;
DeviceMode EEMEM polivMode = DEFAULT_MODE;

I2CAddress EEMEM slaveAddress = I2C_SLAVE_ADDRESS;
}


void PolivSettings::setMinHumidity(HumidityVal value)
{
    eeprom_write_word(&backstagemem::minHumidity, (uint16_t)value);
}
void PolivSettings::setMaxHumidity(HumidityVal value)
{
    eeprom_write_word(&backstagemem::maxHumidity, (uint16_t)value);
}
void PolivSettings::setPumpOnTime(TimeSecVal value)
{
    eeprom_write_word(&backstagemem::minPumpOnTime, (uint16_t)value);
}
void PolivSettings::setAbsorbedTime(TimeSecVal value)
{
    eeprom_write_word(&backstagemem::waitTimeAfterpump, (uint16_t)value);
}
void PolivSettings::setDeviceMode(DeviceMode mode)
{
    eeprom_write_byte((uint8_t *)&backstagemem::polivMode, (uint8_t)mode);
}
void PolivSettings::setAddress(I2CAddress addr)
{
    eeprom_write_byte(&backstagemem::slaveAddress, (uint8_t)addr);
}

HumidityVal PolivSettings::getMinHumidity() const
{
    return (HumidityVal)eeprom_read_word(&backstagemem::minHumidity);
}
HumidityVal PolivSettings::getMaxHumidity() const
{
    return (HumidityVal)eeprom_read_word(&backstagemem::maxHumidity);
}
TimeSecVal PolivSettings::getPumpOnTime() const
{
    return (TimeSecVal)eeprom_read_word(&backstagemem::minPumpOnTime);
}
TimeSecVal PolivSettings::getAbsorbedTime() const
{
    return (TimeSecVal)eeprom_read_word(&backstagemem::waitTimeAfterpump);
}
DeviceMode PolivSettings::getDeviceMode() const
{
    return (DeviceMode)eeprom_read_byte((uint8_t *)&backstagemem::polivMode);
}
I2CAddress PolivSettings::getAddress() const
{
    return (I2CAddress)eeprom_read_byte(&backstagemem::slaveAddress);
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
