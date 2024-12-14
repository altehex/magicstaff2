#include <util/delay.h>

#include "adxl.h"
#include "config.h"
#include "magicstaff.h"


void
setup(void)
{
	ADCSRA &= ~(1<<ADPS2);
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);

	DDRD &= (uint8_t) ((0xFF ^ Config::ADXL_INT_PIN) | 0b11);
	attachInterrupt(
			digitalPinToInterrupt(Config::ADXL_INT_PIN),
			MagicStaff::int_notify,
			RISING
	);
	
	Adxl::init();
	MagicStaff::init();
}


void
loop(void)
{
	MagicStaff::run();
}
