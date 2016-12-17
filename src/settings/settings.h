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

typedef uint16_t HumidityVal;
typedef uint16_t TimeSecVal;

class IHerbsHandler
{
public:
    virtual void handleHerbs();
    static void delay_s(uint16_t s)
    {
        for(; s > 0; s--) _delay_ms(1000);
    }
};

class IDeviceModeSettings
{
public:
    virtual void setDeviceMode(DeviceMode mode);
    virtual DeviceMode getDeviceMode() const;
};

class IPolivControl : public IDeviceModeSettings
{
public:
    virtual DeviceStatus getDeviceStatus() const;
    virtual HumidityVal getHumidity();
};

class ISettingsExt
{
public:
    virtual uint8_t getDeviceGUID(uint8_t pos) const;
    virtual uint8_t getDeviceName(uint8_t pos) const;
    virtual uint8_t getDeviceSWver(uint8_t pos) const;
    virtual uint8_t getDeviceHWver(uint8_t pos) const;

    virtual void setMinHumidity(HumidityVal value);
    virtual void setMaxHumidity(HumidityVal value);
    virtual void setPumpOnTime(TimeSecVal value);
    virtual void setAbsorbedTime(TimeSecVal value);

    virtual HumidityVal getMinHumidity() const;
    virtual HumidityVal getMaxHumidity() const;
    virtual TimeSecVal getPumpOnTime() const;
    virtual TimeSecVal getAbsorbedTime() const;
};

class ISettingsInt : public ISlaveAddress, public IDeviceModeSettings
{
public:
    virtual HumidityVal getMinHumidity() const;
    virtual HumidityVal getMaxHumidity() const;
    virtual TimeSecVal getPumpOnTime() const;
    virtual TimeSecVal getAbsorbedTime() const;
};

class PolivSettings : public ISettingsInt, public ISettingsExt
{
public:
    void setDeviceMode(DeviceMode mode);
    void setMinHumidity(HumidityVal value);
    void setMaxHumidity(HumidityVal value);
    void setPumpOnTime(TimeSecVal value);
    void setAbsorbedTime(TimeSecVal value);
    void setAddress(I2CAddress newAddr);

    DeviceMode getDeviceMode() const;
    HumidityVal getMinHumidity() const;
    HumidityVal getMaxHumidity() const;
    TimeSecVal getPumpOnTime() const;
    TimeSecVal getAbsorbedTime() const;
    I2CAddress getAddress() const;

    uint8_t getDeviceGUID(uint8_t pos) const;
    uint8_t getDeviceName(uint8_t pos) const;
    uint8_t getDeviceSWver(uint8_t pos) const;
    uint8_t getDeviceHWver(uint8_t pos) const;
};

#endif // SETTINGS_H
