#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <settings.h>
#include <hwiface.h>
#include <mappedmemory.h>
#include <server.h>


void delay_s(uint16_t s);
void handleHerbs();

HWiface * hdware;
PolivSettings * stngs;

int main()
{
    auto hardware = HWiface::instance();
    hdware = hardware;
    hardware->init();

    PolivSettings settings;
    MappedMemory memory(&settings);
    stngs = &settings;

    UsiTwiSlave network(USI::instance());
    I2CSlaveServer server(&network, &memory);
    network.init(settings.getI2cAddress(), MULTICAST_ADDR);

    _delay_ms(500);
    sei();
    hardware->turnLedOn();

    while(1) {
        handleHerbs();
        _delay_ms(10000);
    }

    return 0;
}


void handleHerbs()
{
    if(hdware->humidity() < stngs->getMinHumidity())
        while(hdware->humidity() < stngs->getMaxHumidity()) {
            hdware->turnPumpOn();
            delay_s(stngs->getMinPumpOnTime());
            hdware->turnPumpOff();
            delay_s(stngs->getWaitTimeAfterpump());
        }
}

void delay_s(uint16_t s)
{
    for(; s > 0; s--) _delay_ms(1000);
}
