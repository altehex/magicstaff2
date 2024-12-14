#include "adxl.h"


#include <Wire.h>


namespace Adxl {


float thisCoords[3], lastCoords[3];
uint8_t intMask = 0;


void
get_coords(float * coords)
{
	float gains[3] = {
		0.0037639,
		0.00376009,
		0.00349265
	};

	byte tmp[6];

	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(DATAX);
	Wire.endTransmission();

	Wire.requestFrom(I2C_ADDRESS, (uint8_t) 6);
	if (Wire.available())
		for (int i = 0; i < 3; ++i) {
			tmp[i] = Wire.read();
			tmp[i+3] = Wire.read();
			coords[i] = gains[i]*(uint16_t)(tmp[i] | (tmp[i+3]<<8));
		}
}
 
 
}; // namespace Adxl
