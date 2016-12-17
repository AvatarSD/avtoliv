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

ISettingsExt * settings = nullptr; /* settings in eeprom */
IPolivControl * control = nullptr;       /* main poliv iface   */
ITwiSlave * network = nullptr;          /* server pointer to
                                         change address     */

#define readByte(word, addr) ((uint8_t)((word >> (addr * 8)) & 0xFF));

template<typename TypeSize>
int8_t writeWord(TypeSize & staticReg, uint8_t addr, uint8_t data)
{
    if(addr == 0) staticReg = 0;
    staticReg |= (TypeSize)(data << (addr * 8));
    if(addr == sizeof(staticReg) - 1) return OK;
    return ERR;
}

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

class MainHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        static HumidityVal tmp;
        if(addr == 0) tmp = control->getHumidity();
        return readByte(tmp, addr);
    }
};
class MaxHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        static HumidityVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setMaxHumidity(tmp);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        static HumidityVal tmp;
        if(addr == 0) tmp = settings->getMaxHumidity();
        return readByte(tmp, addr);
    }
};
class MinHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        static HumidityVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setMinHumidity(tmp);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        static HumidityVal tmp;
        if(addr == 0) tmp = settings->getMinHumidity();
        return readByte(tmp, addr);
    }
};
class AfterpumpWait : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        static TimeSecVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setAbsorbedTime(tmp);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        static TimeSecVal tmp;
        if(addr == 0) tmp = settings->getAbsorbedTime();
        return readByte(tmp, addr);
    }
};
class PumpOnTime : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        static TimeSecVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setPumpOnTime(tmp);
        return OK;

    }
    static ReadType read(Address addr, Num num = 0)
    {
        static TimeSecVal tmp;
        if(addr == 0) tmp = settings->getPumpOnTime();
        return readByte(tmp, addr);
    }
};
class PumpMode : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        control->setDeviceMode((DeviceMode)data);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getDeviceMode();
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
        return (uint8_t)control->getDeviceStatus();
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
    Composite<GUID, DeviceName, DeviceSWver, DeviceHWver, SlaveAddress> {};

class PolivShared : public
    Composite<MainHumidity, MinHumidity, MaxHumidity, PumpOnTime,
    AfterpumpWait, PolivStatus, PumpMode> {};


class MainMem : public
    Composite<CommonShared, PolivShared, _res_> {};

static_assert(sizeof(MainMem) == 256, "MainMen is not 256bytes in size");

typedef MainMem MemoryMammer;
MappedMemory::MappedMemory(ISettingsExt * settngs,
                           IPolivControl * contrl,
                           ITwiSlave * net)
{
    settings = settngs;
    control = contrl;
    network = net;
    SlaveAddress::setISlaveAddress(net);
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
