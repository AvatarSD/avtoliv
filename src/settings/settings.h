#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>
#include <util/delay.h>
#include <usiTwiSlave.h>

#define VER(MAJOR, MINOR) ((MAJOR << 8)|(MINOR))

// hardware defined settings
#define GUID_SIZE 16
#define DEVNAME_SIZE 4
#define RESERVED_SIZE 219

//poliv
#define DEV_NAME {'a', 'p', 'l', 'v'}
#define DEV_SW_VER VER(1, 0)
#define DEV_HW_VER VER(0, 1)

//default instance for first-time program
#define I2C_SLAVE_ADDRESS 0x15
#define DEFAULT_MODE DeviceMode::Auto
#define DEFAULT_MINHUMODITY 350
#define DEFAULT_MAXHUMODITY 700
#define DEFAULT_PUMPTIME 4
#define DEFAULT_AFTERPUMPTIME 120


enum DeviceStatus {
    WaitForMinHumidity,
    PumpOn,
    AfterPumpWait
};
enum DeviceMode {
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
    virtual void setMode(DeviceMode);
    virtual DeviceMode getPolivMode();
    virtual DeviceStatus getStatus();
    virtual uint16_t getHumidity(uint8_t);
};

class IPolivSettingsExt: public ISlaveAddress
{
public:
    virtual uint8_t getMinHumidity(uint8_t pos) const;
    virtual void setMinHumidity(uint8_t value, uint8_t pos);

    virtual uint8_t getMaxHumidity(uint8_t pos) const;
    virtual void setMaxHumidity(uint8_t value, uint8_t pos);

    virtual uint8_t getMinPumpOnTime(uint8_t pos) const;
    virtual void setMinPumpOnTime(uint8_t value, uint8_t pos);

    virtual uint8_t getWaitTimeAfterpump(uint8_t pos) const;
    virtual void setWaitTimeAfterpump(uint8_t value, uint8_t pos);

    virtual uint8_t getMode() const;
    virtual void setMode(uint8_t mode);

    virtual uint8_t getAddress() const;
    virtual void setAddress(uint8_t newAddr);

    virtual uint8_t getDeviceGUID(uint8_t pos) const;
    virtual uint8_t getDeviceName(uint8_t pos) const;
    virtual uint8_t getDeviceSWver(uint8_t pos) const;
    virtual uint8_t getDeviceHWver(uint8_t pos) const;
};

class IPolivSettingsInt : public ISlaveAddress
{
public:
    virtual uint16_t getMinHumidity() const;
    virtual void setMinHumidity(const uint16_t & value);

    virtual uint16_t getMaxHumidity() const;
    virtual void setMaxHumidity(const uint16_t & value);

    virtual uint16_t getMinPumpOnTime() const;
    virtual void setMinPumpOnTime(const uint16_t & value);

    virtual uint16_t getWaitTimeAfterpump() const;
    virtual void setWaitTimeAfterpump(const uint16_t & value);

    virtual DeviceMode getMode();
    virtual void setMode(DeviceMode mode);


    virtual uint8_t getAddress() const;
    virtual void setAddress(uint8_t newAddr);
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

    DeviceMode getMode();
    void setMode(DeviceMode mode);


    uint8_t getMinHumidity(uint8_t pos) const;
    void setMinHumidity(uint8_t value, uint8_t pos);

    uint8_t getMaxHumidity(uint8_t pos) const;
    void setMaxHumidity(uint8_t value, uint8_t pos);

    uint8_t getMinPumpOnTime(uint8_t pos) const;
    void setMinPumpOnTime(uint8_t value, uint8_t pos);

    uint8_t getWaitTimeAfterpump(uint8_t pos) const;
    void setWaitTimeAfterpump(uint8_t value, uint8_t pos);

    uint8_t getMode() const;
    void setMode(uint8_t mode);


    uint8_t getAddress() const;
    void setAddress(uint8_t newAddr);

    uint8_t getDeviceGUID(uint8_t pos) const;
    uint8_t getDeviceName(uint8_t pos) const;
    uint8_t getDeviceSWver(uint8_t pos) const;
    uint8_t getDeviceHWver(uint8_t pos) const;


};

#endif // SETTINGS_H
