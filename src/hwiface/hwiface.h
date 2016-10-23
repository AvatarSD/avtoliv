#ifndef HWIFACE_H
#define HWIFACE_H

#include <inttypes.h>

class HWiface
{
public:
	static bool haveSupply();
	static uint16_t humidity();
	static void turnSensorOn();
	static void turnSensorOff();
	static void turnLedOff();
	static void turnLedOn();
	static void turnPumpOn();
	static void turnPumpOff();
	static void init();

private:
	HWiface() {}
	HWiface( const HWiface& );
	HWiface& operator=( HWiface& );

};

#endif // HWIFACE_H
