#ifndef MAPPEDMEMORY_H
#define MAPPEDMEMORY_H

#include <server.h>
#include <settings.h>
#include <idcells.h>


#define readByte(word, addr) ((uint8_t)((word >> (addr * 8)) & 0xFF));

template<typename TypeSize>
int8_t writeWord(TypeSize & staticReg, uint8_t addr, uint8_t data)
{
    if(addr == 0) staticReg = 0;
    staticReg |= (TypeSize)(data << (addr * 8));
    if(addr == sizeof(staticReg) - 1) return OK;
    return ERR;
}

class MainHumidity : public IMemory
{
public:
    MainHumidity(IPolivControl * control) : control(control) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        if(addr == 0) tmp = control->getHumidity();
        return readByte(tmp, addr);
    }
    size_t size()
    {
        return sizeof(HumidityVal);
    }
private:
    IPolivControl * control;
    HumidityVal tmp;
};
class MaxHumidity : public IMemory
{
public:
    MaxHumidity(ISettingsExt * settings) : settings(settings) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        if(writeWord(tmp_w, addr, data) == OK)
            settings->setMaxHumidity(tmp_w);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        if(addr == 0) tmp_r = settings->getMaxHumidity();
        return readByte(tmp_r, addr);
    }
    size_t size()
    {
        return sizeof(HumidityVal);
    }
private:
    ISettingsExt * settings;
    HumidityVal tmp_r, tmp_w;
};
class MinHumidity : public IMemory
{
public:
    MinHumidity(ISettingsExt * settings) : settings(settings) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        if(writeWord(tmp_w, addr, data) == OK)
            settings->setMinHumidity(tmp_w);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        if(addr == 0) tmp_r = settings->getMinHumidity();
        return readByte(tmp_r, addr);
    }
    size_t size()
    {
        return sizeof(HumidityVal);
    }
private:
    ISettingsExt * settings;
    HumidityVal tmp_r, tmp_w;
};
class AfterpumpWait : public IMemory
{
public:
    AfterpumpWait(ISettingsExt * settings) : settings(settings) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        if(writeWord(tmp_w, addr, data) == OK)
            settings->setAbsorbedTime(tmp_w);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        if(addr == 0) tmp_r = settings->getAbsorbedTime();
        return readByte(tmp_r, addr);
    }
    size_t size()
    {
        return sizeof(TimeSecVal);
    }
private:
    ISettingsExt * settings;
    TimeSecVal tmp_r, tmp_w;
};
class PumpOnTime : public IMemory
{
public:
    PumpOnTime(ISettingsExt * settings) : settings(settings) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        if(writeWord(tmp_w, addr, data) == OK)
            settings->setPumpOnTime(tmp_w);
        return OK;

    }
    ReadType read(Address addr, Num num = 0)
    {
        if(addr == 0) tmp_r = settings->getPumpOnTime();
        return readByte(tmp_r, addr);
    }
    size_t size()
    {
        return sizeof(TimeSecVal);
    }

private:
    ISettingsExt * settings;
    TimeSecVal tmp_r, tmp_w;
};
class PumpMode : public IMemory
{
public:
    PumpMode(IPolivControl * control) : control(control) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        control->setDeviceMode((DeviceMode)data);
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getDeviceMode();
    }
    size_t size()
    {
        return sizeof(uint8_t);
    }
private:
    IPolivControl * control;
};
class PolivStatus : public IMemory
{
public:
    PolivStatus(IPolivControl * control) : control(control) {}
    Error write(Address addr, uint8_t data, Num num)
    {
        return OK;
    }
    ReadType read(Address addr, Num num = 0)
    {
        return (uint8_t)control->getDeviceStatus();
    }
    size_t size()
    {
        return sizeof(uint8_t);
    }
private:
    IPolivControl * control;
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

class PolivShared : public
    Composite<MainHumidity, MinHumidity, MaxHumidity, PumpOnTime,
    AfterpumpWait, PolivStatus, PumpMode>
{
public:
    PolivShared(IPolivControl * control, ISettingsExt * settings) :
        Composite(&humidity, &minHumidity, &maxHumidity,
                  &pumpOnTime, &afterpumpWait, &status,
                  &mode),
        humidity(control), minHumidity(settings),
        maxHumidity(settings), pumpOnTime(settings),
        afterpumpWait(settings), status(control), mode(control) {}

private:
    MainHumidity humidity;
    MinHumidity minHumidity;
    MaxHumidity maxHumidity;
    PumpOnTime pumpOnTime;
    AfterpumpWait afterpumpWait;
    PolivStatus status;
    PumpMode mode;
};


class MainMem : public
    Composite<CommonShared, PolivShared, _res_>
{
public:
    MainMem(IPolivControl * control, ISettingsExt * settings) :
        Composite(&shared, &poliv, &res),
        shared(settings), poliv(control, settings) {}

    void setNetworkObject(ISlaveAddress * iAddress)
    {
        shared.setNetworkObject(iAddress);
    }
private:
    CommonShared shared;
    PolivShared poliv;
    _res_ res;
};



#endif // MAPPEDMEMORY_H
