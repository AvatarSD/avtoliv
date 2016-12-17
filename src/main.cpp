#include <avr/io.h>
#include <avr/interrupt.h>
#include <settings.h>
#include <mappedmemory.h>
#include <server.h>
#include <herbshandlersimpl.h>


// here is a default one
#define MULTICAST_ADDR 0x30

int main()
{
    auto hardware = HWiface::instance();
    hardware->init();

    PolivSettings settings;
    HerbsHandlerSimpl herbshandler(hardware, &settings);

    UsiTwiSlave network(USI::instance(), &settings, MULTICAST_ADDR);
    MappedMemory memory(&settings, &herbshandler, &network);

    I2CSlaveServer server(&network, &memory);

    network.init();
    hardware->turnLedOn();
    sei();

    while(1) {
        herbshandler.handleHerbs();
        herbshandler.delay_s(10);
    }

    return 0;
}
