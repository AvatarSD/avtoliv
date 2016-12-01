#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <hwiface.h>
#include <mappedmemory.h>



#define I2C_ADDR  0x05
#define I2C_COMMN 0x10


void delay_s(uint16_t s);
void handleHerbs();

int main()
{
    auto hardware = HWiface::instance();
    hardware->init();

    auto usi = USI::instance();

    PolivSettings settings;
    MappedMemory memory(&settings);

    UsiTwiSlave network(usi);
    network.setAddress(I2C_SLAVE_ADDRESS);
    network.setMulticastAddress(MULTICAST_ADDRESS);
    I2CSlaveServer server(&network, &memory);



    network.init();



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
    if(hardware->humidity() < settings.getMinHumidity())
        while(hardware->humidity() < settings.getMaxHumidity()) {
            hardware->turnPumpOn();
            delay_s(settings.getMinPumpOnTime());
            hardware->turnPumpOff();
            delay_s(settings.getWaitTimeAfterpump());
        }
}

void delay_s(uint16_t s)
{
    for(; s > 0; s--) _delay_ms(1000);
}
