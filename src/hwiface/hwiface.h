#ifndef HWIFACE_H
#define HWIFACE_H

#include <inttypes.h>

class HWiface
{
public:
	bool haveSupply();
	uint16_t humidity();
	void turnSensorOn();
	void turnSensorOff();
	void turnLedOff();
	void turnLedOn();
	void turnPumpOn();
	void turnPumpOff();
	void init();

	static HWiface*instance(){
		static HWiface iface;
		return &iface;
	}

private:
	HWiface() {}
	HWiface( const HWiface& );
	HWiface& operator=( HWiface& );

};

#endif // HWIFACE_H
