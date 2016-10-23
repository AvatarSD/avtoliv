#include <avr/io.h>
#include <util/delay.h>
#include "hwiface/hwiface.h"

#include <avr/io.h>

uint16_t min_humidity = 50;
uint16_t max_humidity = 200;
uint16_t min_pump_on_time = 6;
uint16_t wait_time_afterpump = 30;

void delay_s(uint16_t s) {
	for(; s > 0; s--) _delay_ms(1000);
}

void handleHerbs()
{
	if(HWiface::humidity() < min_humidity)
		while(HWiface::humidity() < max_humidity)
		{
			HWiface::turnPumpOn();
			delay_s(min_pump_on_time);
			HWiface::turnPumpOff();
			delay_s(wait_time_afterpump);
		}
}

int main()
{
	HWiface::init();

	_delay_ms(500);
	HWiface::turnLedOn();


	while(1)
	{
		handleHerbs();
		_delay_ms(10000);

	}
	return 0;
}
