#include "hwiface.h"
#include <avr/io.h>

// pump hv ac supply
#define DDR_PUMP DDRB
#define PORT_PUMP PORTB
#define PINNUM_PUMP 3

// power of status led
#define DDR_LED DDRB
#define PORT_LED PORTB
#define PINNUM_LED 1
#define LED_OFFSTATE false

// +5v to humiditi sensor
#define DDR_SUPL DDRB
#define PORT_SENS_SUPL PORTB
#define PINNUM_SENS_SUPL  1

// num of sensor date analog  pin
#define ADC_SENS 1

// num of analog pin to testing presense of main power(supplying by network)
#define ADC_AC 3


uint16_t HWiface::humidity()
{
	return 0;

}

bool HWiface::haveSupply()
{


	return 0;
}

void HWiface::turnSensorOnLedOff()
{

}

void HWiface::turnSensorOffLedOn()
{

}

void HWiface::turnSensorOffLedOff()
{

}

void HWiface::turnPumpOn()
{

}

void HWiface::turnPumpOff()
{

}

void HWiface::init()
{
	DDRB |= 1<<1;
}
