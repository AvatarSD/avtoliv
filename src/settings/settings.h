#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>

#define VER(MAJOR, MINOR) ((MAJOR << 8)|(MINOR))

// hardware defined settings
#define GUID_SIZE 16
#define DEVNAME_SIZE 4

#define DEV_NAME {'a', 'p', 'l', 'v'}
#define DEV_SW_VER VER(0, 5)
#define DEV_HW_VER VER(0, 1)

// here is a default one
#define MULTICAST_ADDR 0x50

//default instance for first-time program
#define I2C_SLAVE_ADDRESS 0x15




class PolivSettings
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


    void setI2cAddress(uint8_t newAddr);
    uint8_t getI2cAddress();

    uint8_t getGUID(uint8_t pos);
    uint8_t getDeviceName(uint8_t pos);
    uint8_t getDeviceSWver(uint8_t pos);
    uint8_t getDeviceHWver(uint8_t pos);


};

#endif // SETTINGS_H
