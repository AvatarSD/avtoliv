#include "hwiface.h"
#include <avr/io.h>
#include <util/delay.h>

// pump supply
#define DDR_PUMP DDRB
#define PORT_PUMP PORTB
#define PINNUM_PUMP 3
#define PUMP_OFFSTATE false

// power of status led
#define DDR_LED DDRB
#define PORT_LED PORTB
#define PINNUM_LED 1
#define LED_OFFSTATE false

// humiditi sensor
// +5v to sensor
#define DDR_SENS_SUPL DDRB
#define PORT_SENS_SUPL PORTB
#define PINNUM_SENS_SUPL  1
#define SENS_OFFSTATE true
// num of sensor date analog  pin
#define ADC_SENS 2

// analog pin to testing presense of main power(supplying by network)
#define ADC_AC 3
#define DDR_AC DDRB
#define PORT_AC PORTB
#define PINNUM_AC 3
#define TRESHOLD_DATA_AC 80





#define setbit(port,num,onoff) port=(onoff<<num)|(port&~(1<<num))

uint16_t HWiface::humidity()
{
	return 0; // todo read adc

}

bool HWiface::haveSupply()
{
	uint8_t ddrBackup = DDR_AC;
	DDR_AC &= ~_BV(PINNUM_AC);

	_delay_us(10);

	uint16_t adcData = 0;// todo read adc

	bool ret_val;
	if(adcData > TRESHOLD_DATA_AC)
		ret_val = true;
	else
		ret_val = false;

	DDR_AC = ddrBackup;

	return ret_val;
}

void HWiface::turnSensorOn()
{
	DDR_SENS_SUPL |= _BV(PINNUM_SENS_SUPL);
	setbit(PORT_SENS_SUPL, PINNUM_SENS_SUPL, !SENS_OFFSTATE);
}

void HWiface::turnSensorOff()
{
	DDR_SENS_SUPL |= _BV(PINNUM_SENS_SUPL);
	setbit(PORT_SENS_SUPL, PINNUM_SENS_SUPL, SENS_OFFSTATE);
}

void HWiface::turnLedOff()
{
	DDR_LED &= ~_BV(PINNUM_LED);
}

void HWiface::turnLedOn()
{
	DDR_LED |= _BV(PINNUM_LED);
	setbit(PORT_LED, PINNUM_LED, !LED_OFFSTATE);
}

void HWiface::turnPumpOn()
{
	DDR_PUMP |= _BV(PINNUM_PUMP);
	PORT_PUMP |= _BV(PINNUM_PUMP);
}

void HWiface::turnPumpOff()
{
	DDR_PUMP |= _BV(PINNUM_PUMP);
	PORT_PUMP &= ~_BV(PINNUM_PUMP);
}

void HWiface::init()
{
	turnPumpOff();
	turnSensorOff();
	turnLedOn();
}


