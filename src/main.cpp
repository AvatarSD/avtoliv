#include <avr/io.h>
#include <util/delay.h>
#include "hwiface/hwiface.h"



int main()
{
	HWiface::init();

	while(1)
	{
		HWiface::turnLedOn();
		_delay_ms(2000);

		HWiface::turnPumpOn();
		_delay_ms(2000);

		HWiface::turnPumpOff();
		_delay_ms(1000);

		HWiface::turnSensorOn();
		_delay_ms(20);

		HWiface::turnSensorOff();
		_delay_ms(2000);

		HWiface::turnLedOff();
		_delay_ms(3000);
	}
	return 0;
}
