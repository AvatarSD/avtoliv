#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>
#include <util/delay.h>

#define VER(MAJOR, MINOR) ((MAJOR << 8)|(MINOR))

// hardware defined settings
#define GUID_SIZE 16
#define DEVNAME_SIZE 4

#define DEV_NAME {'a', 'p', 'l', 'v'}
#define DEV_SW_VER VER(0, 5)
#define DEV_HW_VER VER(0, 1)

//default instance for first-time program
#define I2C_SLAVE_ADDRESS 0x15

enum PolivStage {
    WaitForMinHumidity,
    PumpOn,
    AfterPumpWait
};
enum PolivMode {
    ManualOff = 0,
    ManualOn = 1,
    Auto = 2
};


class IHerbsHandler
{
public:
    virtual void handleHerbs();

    static void delay_s(uint16_t s)
    {
        for(; s > 0; s--) _delay_ms(1000);
    }
};

class IPolivControl
{
public:
    virtual void setMode(PolivMode);
    virtual PolivMode getPolivMode();
    virtual PolivStage getStatus();
};

class IPolivSettingsExt
{
public:
    virtual uint8_t getHumidity(uint8_t pos) const;
    virtual void setHumidity(uint8_t value, uint8_t pos);

    virtual uint8_t getMinHumidity(uint8_t pos) const;
    virtual void setMinHumidity(uint8_t value, uint8_t pos);

    virtual uint8_t getMaxHumidity(uint8_t pos) const;
    virtual void setMaxHumidity(uint8_t value, uint8_t pos);

    virtual uint8_t getMinPumpOnTime(uint8_t pos) const;
    virtual void setMinPumpOnTime(uint8_t value, uint8_t pos);

    virtual uint8_t getWaitTimeAfterpump(uint8_t pos) const;
    virtual void setWaitTimeAfterpump(uint8_t value, uint8_t pos);


    virtual uint8_t getI2cAddress() const;
    virtual void setI2cAddress(uint8_t newAddr);

    virtual uint8_t getGUID(uint8_t pos) const;
    virtual uint8_t getDeviceName(uint8_t pos) const;
    virtual uint8_t getDeviceSWver(uint8_t pos) const;
    virtual uint8_t getDeviceHWver(uint8_t pos) const;
};

class IPolivSettingsInt
{
public:
    virtual uint16_t getHumidity() const;
    virtual void setHumidity(const uint16_t & value);

    virtual uint16_t getMinHumidity() const;
    virtual void setMinHumidity(const uint16_t & value);

    virtual uint16_t getMaxHumidity() const;
    virtual void setMaxHumidity(const uint16_t & value);

    virtual uint16_t getMinPumpOnTime() const;
    virtual void setMinPumpOnTime(const uint16_t & value);

    virtual uint16_t getWaitTimeAfterpump() const;
    virtual void setWaitTimeAfterpump(const uint16_t & value);


    virtual uint8_t getI2cAddress() const;
    virtual void setI2cAddress(uint8_t newAddr);
};

class PolivSettings : public IPolivSettingsInt, public IPolivSettingsExt
{
public:
    uint16_t getHumidity() const;
    void setHumidity(const uint16_t & value);

    uint16_t getMinHumidity() const;
    void setMinHumidity(const uint16_t & value);

    uint16_t getMaxHumidity() const;
    void setMaxHumidity(const uint16_t & value);

    uint16_t getMinPumpOnTime() const;
    void setMinPumpOnTime(const uint16_t & value);

    uint16_t getWaitTimeAfterpump() const;
    void setWaitTimeAfterpump(const uint16_t & value);


    uint8_t getHumidity(uint8_t pos) const;
    void setHumidity(uint8_t value, uint8_t pos);

    uint8_t getMinHumidity(uint8_t pos) const;
    void setMinHumidity(uint8_t value, uint8_t pos);

    uint8_t getMaxHumidity(uint8_t pos) const;
    void setMaxHumidity(uint8_t value, uint8_t pos);

    uint8_t getMinPumpOnTime(uint8_t pos) const;
    void setMinPumpOnTime(uint8_t value, uint8_t pos);

    uint8_t getWaitTimeAfterpump(uint8_t pos) const;
    void setWaitTimeAfterpump(uint8_t value, uint8_t pos);


    uint8_t getI2cAddress() const;
    void setI2cAddress(uint8_t newAddr);

    uint8_t getGUID(uint8_t pos) const;
    uint8_t getDeviceName(uint8_t pos) const;
    uint8_t getDeviceSWver(uint8_t pos) const;
    uint8_t getDeviceHWver(uint8_t pos) const;


};

#endif // SETTINGS_H
