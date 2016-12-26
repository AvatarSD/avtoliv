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

    PolivSettings settings;
    HerbsHandlerSimpl herbshandler(hardware, &settings);

    MainMem memory(&herbshandler, &settings);
    I2CSlaveServer server(&memory);
    UsiTwiSlave network(USI::instance(), &server, &settings, MULTICAST_ADDR);

    memory.setNetworkObject(&network);
    hardware->init();
    network.init();
    hardware->turnLedOn();
    sei();

    while(1) {
        herbshandler.handleHerbs();
        herbshandler.delay_s(10);
    }

    return 0;
}
