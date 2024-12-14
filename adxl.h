#ifndef __ADXL_H
#define __ADXL_H


#include <Wire.h>

#include "config.h"
#include <Arduino.h>


namespace Adxl {

	
extern float thisCoords[3], lastCoords[3];
extern uint8_t intMask;


void get_coords(void);
	
	
const uint8_t I2C_ADDRESS = 0x1D;

const uint8_t REG_POWER_CTL = 0x2D,
	WAKEUP_8 = 0x00,
	MEASURE  = 0x08;

const uint8_t REG_DATA_FORMAT = 0x31;

const uint8_t REG_TAP_THRESH = 0x1D;

const uint8_t REG_DUR = 0x21;

const uint8_t REG_TAP_AXES = 0x2A,
	X = 1<<2,
	Y = 1<<1,
	Z = 1<<0;

const uint8_t REG_WINDOW = 0x23;

const uint8_t REG_LATENCY = 0x22;

const uint8_t REG_INT_MAP    = 0x2F,
	          REG_INT_ENABLE = 0x2E,
	          REG_INT_SOURCE = 0x30,
	DATA_READY = 1<<7,
	SINGLE_TAP = 1<<6,
	DOUBLE_TAP = 1<<5,
	ACTIVITY   = 1<<4,
	INACTIVITY = 1<<3,
	FREE_FALL  = 1<<2;

const uint8_t DATAX = 0x32;
	

static inline void
send(uint8_t address, uint8_t data)
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(address);
	Wire.write(data);
	Wire.endTransmission();
}


__attribute__((always_inline))
inline void
get_int_mask(void) {
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(REG_INT_SOURCE);
	Wire.endTransmission();
		
	Wire.requestFrom(I2C_ADDRESS, (uint8_t) 1);
	if (Wire.available())
		intMask = Wire.read();
}


__attribute__((always_inline))
inline void
init(void)
{
	uint8_t durConstrained, threshConstrained;
	
	Wire.begin();
	
	send(REG_POWER_CTL, WAKEUP_8);
	send(REG_DATA_FORMAT, Config::ADXL_RES*3/16);
	send(REG_POWER_CTL, MEASURE);
	
	durConstrained = constrain(Config::TAP_DUR/0.000625f, 0, 0xFF);
	threshConstrained = constrain(Config::TAP_THRESH/0.0625f, 0, 0xFF);
		
	send(REG_TAP_AXES, X|Y|Z);
	send(REG_TAP_THRESH, threshConstrained);
	send(REG_DUR, durConstrained);
	
	send(REG_INT_MAP, SINGLE_TAP);

	get_int_mask();
	send(REG_INT_ENABLE, intMask|SINGLE_TAP);
}
 
 
}; // namespace Adxl


#endif // !__ADXL_H
