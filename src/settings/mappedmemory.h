#ifndef MAPPEDMEMORY_H
#define MAPPEDMEMORY_H

#include <server.h>
#include <settings.h>


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
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num)
    {
        return settings->getDeviceGUID(addr);
    }
};
class DeviceName : public Composite<uint8_t[DEVNAME_SIZE]>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settings->getDeviceName(addr);
    }
};
class DeviceSWver : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settings->getDeviceSWver(addr);
    }
};
class DeviceHWver : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return settings->getDeviceHWver(addr);
    }
};

class MainHumidity : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        static HumidityVal tmp;
        if(addr == 0) tmp = control->getHumidity();
        return readByte(tmp, addr);
    }
};
class MaxHumidity : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        static HumidityVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setMaxHumidity(tmp);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        static HumidityVal tmp;
        if(addr == 0) tmp = settings->getMaxHumidity();
        return readByte(tmp, addr);
    }
};
class MinHumidity : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        static HumidityVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setMinHumidity(tmp);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        static HumidityVal tmp;
        if(addr == 0) tmp = settings->getMinHumidity();
        return readByte(tmp, addr);
    }
};
class AfterpumpWait : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        static TimeSecVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setAbsorbedTime(tmp);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        static TimeSecVal tmp;
        if(addr == 0) tmp = settings->getAbsorbedTime();
        return readByte(tmp, addr);
    }
};
class PumpOnTime : public Composite<uint16_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        static TimeSecVal tmp;
        if(writeWord(tmp, addr, data) == OK)
            settings->setPumpOnTime(tmp);
        return OK;

    }
    ReadType read(Address addr, Num num = 0)
    {
        static TimeSecVal tmp;
        if(addr == 0) tmp = settings->getPumpOnTime();
        return readByte(tmp, addr);
    }
};
class PumpMode : public Composite<uint8_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        control->setDeviceMode((DeviceMode)data);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getDeviceMode();
    }
};
class PolivStatus : public Composite<uint8_t>
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getDeviceStatus();
    }
};

class _res_ : public IMemory
{
public:
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return 0x00;
    }
    size_t size()
    {
        return RESERVED_SIZE;
    }

};

//class CommonShared : public
//    Composite<GUID, DeviceName, DeviceSWver, DeviceHWver, SlaveAddress> {};

class PolivShared : public
    Composite<MainHumidity, MinHumidity, MaxHumidity, PumpOnTime,
    AfterpumpWait, PolivStatus, PumpMode> {};


class MainMem : public
    Composite<CommonShared, PolivShared, _res_> {};



#endif // MAPPEDMEMORY_H
