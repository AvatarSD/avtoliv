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






class GUID : public Composite<uint8_t[GUID_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num)
    {
        return settng->getGUID(addr);
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
        return settng->getDeviceName(addr);
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
        return settng->getDeviceSWver(addr);
    }
};
class DeviceHWver : public Composite<uint16_t>
{
public:
    DeviceHWver(IPolivSettingsExt * setting) : settng(setting) {}

    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settng->getDeviceHWver(addr);
    }

private:
    IPolivSettingsExt * settng;
};

class Humidity : public Composite<uint16_t>
{
public:
    Humidity(IPolivSettingsExt * setting) : settng(setting) {}

    Error write(Address addr, uint8_t data, Num num)
    {
        settng->setHumidity(data, addr);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settng->getHumidity(addr);
    }

private:
    IPolivSettingsExt * settng;
};
class MaxHumidity : public Composite<uint16_t>
{
public:
    MaxHumidity(IPolivSettingsExt * setting) : settng(setting) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        settng->setMaxHumidity(data, addr);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settng->getMaxHumidity(addr);
    }

private:
    IPolivSettingsExt * settng;
};
class MinHumidity : public Composite<uint16_t>
{
public:
    MinHumidity(IPolivSettingsExt * setting) : settng(setting) {}

    Error write(Address addr, uint8_t data, Num num)
    {
        settng->setMinHumidity(data, addr);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settng->getMinHumidity(addr);
    }

private:
    IPolivSettingsExt * settng;
};
class AfterpumpWait : public Composite<uint16_t>
{
public:
    AfterpumpWait(IPolivSettingsExt * setting) : settng(setting) {}

    Error write(Address addr, uint8_t data, Num num)
    {
        settng->setWaitTimeAfterpump(data, addr);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settng->getWaitTimeAfterpump(addr);
    }

private:
    IPolivSettingsExt * settng;
};
class PumpOnTime : public Composite<uint16_t>
{
public:
    PumpOnTime(IPolivSettingsExt * settng) : settng(setting) {}

    Error write(Address addr, uint8_t data, Num num)
    {
        settng->setMinPumpOnTime(data, addr);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settng->getMinPumpOnTime(addr);
    }

private:
    IPolivSettingsExt * settng;
};











//todo: repair; make static method in adresskeeper to set  the variable;

//AddressKeeper::setAddress(MappedMemory::mcastAdr, MappedMemory::servr,
//                          MappedMemory::settng);
typedef SlaveAddress<MappedMemory::mcastAdr, MappedMemory::servr, MappedMemory::settng>
MySlaveAddrr;

class CommonShared : public
    Composite<GUID, DeviceName, DeviceSWver, DeviceHWver, MySlaveAddrr> {};

class MainMemoryMap : public Composite<CommonShared,
    Humidity, MaxHumidity, MinHumidity, PumpOnTime, AfterpumpWait> {};


MainMemoryMap map;

MappedMemory::MappedMemory(IPolivSettingsExt * settings,
                           IPolivControl * control,
                           ITwiSlave * server,
                           IMulticastAddress * iaddr)
{
    settng = settings;
    ctrl = control;
    servr = server;
    mcastAdr = iaddr;
}
int8_t MappedMemory::write(uint8_t addr, uint8_t data)
{
    return map.write(addr, data);
}
int16_t MappedMemory::read(uint8_t addr)
{
    return map.read(addr);
}
uint16_t MappedMemory::mapsize()
{
    return map.size();
}
