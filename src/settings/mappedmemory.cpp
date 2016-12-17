/*
 * by S.D.
 * avatarsd.com
 */

/* I2C Memory Map
 * __________________HEADER_____________________
 * |__START__|__SIZE__|_DESCRIPTIONS_|_OPTIONS_|
 * |0        |16      |guid          |ro       |
 * |16       |1       |i2c addr      |ro       |
 * |17       |2       |require temp  |rw       |
 * |19       |1       |sensors count |ro       |
 * |20       |2       |[res]stat&ctl |rw       |
 * ---------------------------------------------
 * |SIZE: 22 |
 *
 * ________________Device Node__________________
 * |__START__|__SIZE__|_DESCRIPTIONS_|_OPTIONS_|
 * |0        |8       |ROM           |ro       |
 * |8        |2       |Temp          |ro       |
 * |10       |1       |[res]stat&ctl |rw       |
 * ---------------------------------------------
 * |SIZE: 11 |
 *
 * ___________________Main__________________
 * |__START__|__SIZE__|____DESCRIPTIONS____|
 * |0        |21      |HEADER              |
 * |22       |13      |[res]               |
 * |35+N     |46+N    |Nodes(N={0..19})    |
 * -----------------------------------------
 * |SIZE:256 |
 *
 */


#include "mappedmemory.h"
#include <settings.h>
#include <slaveaddres.h>

IPolivSettingsExt * settings = nullptr; /* settings in eeprom */
IPolivControl * control = nullptr;       /* main poliv iface   */
ITwiSlave * servr = nullptr;          /* server pointer to
                                         change address     */

class GUID : public Composite<uint8_t[GUID_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num)
    {
        return settings->getDeviceGUID(addr);
    }
};
class DeviceName : public Composite<uint8_t[DEVNAME_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getDeviceName(addr);
    }
};
class DeviceSWver : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getDeviceSWver(addr);
    }
};
class DeviceHWver : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getDeviceHWver(addr);
    }
};

class Humidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        static uint16_t hum = 0;

        if(addr == 0)
            hum = control->getHumidity(num);

        return (uint8_t)((hum >> (8 * addr)) & 0xff);
    }
};
class MaxHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settings->setMaxHumidity(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getMaxHumidity(addr);
    }
};
class MinHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settings->setMinHumidity(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getMinHumidity(addr);
    }
};
class AfterpumpWait : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settings->setWaitTimeAfterpump(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getWaitTimeAfterpump(addr);
    }
};
class PumpOnTime : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settings->setMinPumpOnTime(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settings->getMinPumpOnTime(addr);
    }
};
class PumpMode : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        control->setMode((DeviceMode)data);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getPolivMode();
    }
};
class PolivStatus : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getStatus();
    }
};

class _res_ : public Composite<uint8_t[RESERVED_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return 0x00;
    }
};

class CommonShared : public
    Composite<GUID, DeviceName, DeviceSWver, DeviceHWver, SlaveAddress<1>> {};

class PolivShared : public
    Composite<Humidity, MaxHumidity, MinHumidity, PumpOnTime,
    AfterpumpWait, PolivStatus, PumpMode> {};


class MainMem : public
    Composite<CommonShared, PolivShared, _res_> {};

static_assert(sizeof(MainMem) == 256, "MainMen is not 256bytes in size");

typedef MainMem MemoryMammer;
MappedMemory::MappedMemory(IPolivSettingsExt * settings,
                           IPolivControl * control,
                           ITwiSlave * server)
{
    settings = settings;
    control = control;
    servr = server;
    SlaveAddress<1>::setAddreses(server, settings);
}
int8_t MappedMemory::write(uint8_t addr, uint8_t data)
{
    return MemoryMammer::write(addr, data);
}
int16_t MappedMemory::read(uint8_t addr)
{
    return MemoryMammer::read(addr);
}
uint16_t MappedMemory::mapsize()
{
    return sizeof(MemoryMammer);
}
