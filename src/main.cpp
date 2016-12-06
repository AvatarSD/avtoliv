#include <avr/io.h>
#include <avr/interrupt.h>
#include <settings.h>
#include <mappedmemory.h>
#include <server.h>
#include <herbshandlersimpl.h>




int main()
{
    auto hardware = HWiface::instance();
    hardware->init();


    PolivSettings settings;
    HerbsHandlerSimpl herbshandler(hardware, &settings);
    MappedMemory memory(&settings, &herbshandler);

    UsiTwiSlave network(USI::instance());
    I2CSlaveServer server(&network, &memory);
    network.init(settings.getI2cAddress(), MULTICAST_ADDR);

    sei();
    hardware->turnLedOn();

    while(1) {
        herbshandler.handleHerbs();
        herbshandler.delay_s(10);
    }

    return 0;
}


