#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <hwiface.h>
#include <mappedmemory.h>



void delay_s(uint16_t s);
void handleHerbs();

HWiface * hdware;
PolivSettings * stngs;

int main()
{
    auto hardware = HWiface::instance();
    hdware = hardware;
    hardware->init();

    auto usi = USI::instance();

    PolivSettings settings;
    stngs = &settings;
    MappedMemory memory(&settings);

    UsiTwiSlave network(usi);
    network.init(I2C_SLAVE_ADDRESS, MULTICAST_ADDRESS);

    I2CSlaveServer server(&network, &memory);






    _delay_ms(500);
    hardware->turnLedOn();

    sei();

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
