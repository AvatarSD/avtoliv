#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>



#define GUID_SIZE 16

#define I2C_SLAVE_ADDRESS 0x15 // TODO for test
#define MULTICAST_ADDRESS 0x30



class PolivSettings
{
public:
    uint16_t getMinHumidity() const;
    void setMinHumidity(const uint16_t & value);
    uint16_t getMaxHumidity() const;
    void setMaxHumidity(const uint16_t & value);
    uint16_t getMinPumpOnTime() const;
    void setMinPumpOnTime(const uint16_t & value);
    uint16_t getWaitTimeAfterpump() const;
    void setWaitTimeAfterpump(const uint16_t & value);

    void setI2cAddress(uint8_t newAddr);
    uint8_t getI2cAddress();

    uint8_t getGUID(uint8_t pos);

};

#endif // SETTINGS_H
