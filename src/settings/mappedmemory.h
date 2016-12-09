#ifndef MAPPEDMEMORY_H
#define MAPPEDMEMORY_H

#include <server.h>
#include <settings.h>


class MappedMemory : public IMappedMemory
{
public:
    MappedMemory(IPolivSettingsExt * settings, IPolivControl * control,
                 ITwiSlave * server);

    int8_t write(uint8_t addr, uint8_t data);
    int16_t read(uint8_t addr);
    uint16_t mapsize();

    //private:
    //    PolivSettings * settings;

};

#endif // MAPPEDMEMORY_H
