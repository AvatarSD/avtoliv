#include <avr/io.h>
#include <util/delay.h>
#include "hwiface/hwiface.h"

#include <avr/io.h>

void ADCinit()
{

}

int main()
{
	HWiface::init();


	HWiface::turnLedOn();
	_delay_ms(500);
	HWiface::turnLedOff();

	while(1)
	{
		//_delay_ms(1000);

//		if(HWiface::haveSupply())
//			HWiface::turnLedOn();
//		else
//			HWiface::turnLedOff();



//		_delay_ms(1000);

		if(HWiface::humidity() < 950)
			HWiface::turnLedOn();
		else
			HWiface::turnLedOff();
		_delay_ms(150);

		//		HWiface::turnPumpOn();
		//		_delay_ms(2000);

		//		HWiface::turnPumpOff();
		//		_delay_ms(1000);

		//		HWiface::turnSensorOn();
		//		_delay_ms(20);

		//		HWiface::turnSensorOff();
		//		_delay_ms(2000);

		//		HWiface::turnLedOff();
		//		_delay_ms(3000);
	}
	return 0;
}
