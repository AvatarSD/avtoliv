#include <avr/io.h>
#include <util/delay.h>
#include "hwiface.h"





int main()
{
	HWiface::init();

	while(1)
	{
		PORTB &= ~(1<<1);
		_delay_ms(200);

		PORTB |=(1<<1);
		_delay_ms(200);
	}
	return 0;
}
