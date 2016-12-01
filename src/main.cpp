#include <avr/io.h>
#include <util/delay.h>

#include <hwiface.h>
#include <avr/io.h>
#include <mappedmemory.h>



PolivSettings settings;
MappedMemory memory(&settings);
HWiface * hardware = HWiface::instance();


void delay_s(uint16_t s)
{
    for(; s > 0; s--) _delay_ms(1000);
}

void handleHerbs()
{
    if(hardware->humidity() < settings.getMinHumidity())
        while(hardware->humidity() < settings.getMaxHumidity()) {
            hardware->turnPumpOn();
            delay_s(settings.getMinPumpOnTime());
            hardware->turnPumpOff();
            delay_s(settings.getWaitTimeAfterpump());
        }
}

int main()
{
    hardware->init();

    _delay_ms(500);
    hardware->turnLedOn();


    while(1) {
        handleHerbs();
        _delay_ms(10000);
    }

    return 0;
}
