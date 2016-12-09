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
#include <polymorphmemory.h>
#include <settings.h>


IPolivSettingsExt * settng = nullptr;
IPolivControl * ctrl = nullptr;
ITwiSlave * servr = nullptr;

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
    static Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settng->getDeviceHWver(addr);
    }
};

class SlaveAddress : public Composite<uint8_t>
{
public:
    static uint8_t newAddr;
    static bool flag;

    static Error write(Address addr, uint8_t data, Num num)
    {
        //if address is multicast - reset slaveAddress to multicast value immediatly
        if(data == servr->getMulticastAddress()) {
            settng->setI2cAddress(data);
            servr->setAddress(data);
            return OK;
        }

        /*
         * todo: newAddr to ERR at second read(when first read wasn't be here - slave
         * address will not change)
         *
         * first version without possibility to change slave addres selectively
         *
         * Algoritm:
         * 1. Write ${MULTICAST_ADDRESS} by ${MULTICAST_ADDRESS} in to the SlaveAddress cell.
         *    All deveces will must have ${MULTICAST_ADDRESS}
         * 2. Now start the autoaddress procedure at each devices:
         *    2.1. Check whether free cell, which we want to appoint to the device,
         *         which will be "arbitration winner". For examble for first device
         *         it will be the 0x01 cell.
         *    2.2. Write the selected cell number by ${MULTICAST_ADDRESS} in to the
         *         SlaveAddress cell. At all devices, newAddr variable will be contain
         *         writed cell number.
         *    2.3. Start consequentially reading before several cells of SlaveAddress cell for
         *         arbitration procedure. Reading must be consequentially, because we must
         *         read slave address cell only in arbitration winner. Fot example:
         *         SlaveAddress cell at 0x10 address. Before it we have 0x0f bytes of
         *         unique uuid number at each device. When we start reading this cells
         *         by ${MULTICAST_ADDRESS} we get arbitrations: each device, which lose
         *         arbitrations will wait next start contitions. When we read the SlaveAddress
         *         cell at winner device - it will change own slave address and prohibit the
         *         furure reading(will not participate in future arbitration for remaining
         *         devices) while slave addres will change to multicast again.
         *    2.4. ...
         *
         */
        newAddr = data;
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        if(newAddr != ERR) {
            settng->setI2cAddress(newAddr);
            servr->setAddress(newAddr);
        }
        newAddr = ERR;
        return settng->getI2cAddress();
    }
};
int16_t SlaveAddress::newAddr = ERR;

class Humidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settng->setHumidity(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settng->getHumidity(addr);
    }
};
class MaxHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settng->setMaxHumidity(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settng->getMaxHumidity(addr);
    }
};
class MinHumidity : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settng->setMinHumidity(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settng->getMinHumidity(addr);
    }
};
class AfterpumpWait : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settng->setWaitTimeAfterpump(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settng->getWaitTimeAfterpump(addr);
    }
};
class PumpOnTime : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num)
    {
        settng->setMinPumpOnTime(data, addr);
        return OK;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return settng->getMinPumpOnTime(addr);
    }
};

class CommonShared : public
    Composite<GUID, DeviceName, DeviceSWver, DeviceHWver, SlaveAddress> {};

class MainMemoryMap : public Composite<CommonShared,
    Humidity, MaxHumidity, MinHumidity, PumpOnTime, AfterpumpWait> {};

typedef MainMemoryMap Map;

MappedMemory::MappedMemory(IPolivSettingsExt * settings,
                           IPolivControl * control,
                           ITwiSlave * server)
{
    settng = settings;
    ctrl = control;
    servr = server;
}
int8_t MappedMemory::write(uint8_t addr, uint8_t data)
{
    return Map::write(addr, data);
}
int16_t MappedMemory::read(uint8_t addr)
{
    return Map::read(addr);
}
uint16_t MappedMemory::mapsize()
{
    return sizeof(Map);
}
