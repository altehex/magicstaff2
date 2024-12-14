#ifndef __CONFIG_H
#define __CONFIG_H


#define FASTLED_OVERCLOCK 1.2


namespace Config {


const uint8_t LED_COUNT = 47;
const uint8_t BRIGHTNESS = 255;

const uint8_t LED_PIN      = 8;
const uint8_t ADXL_INT_PIN = 3;

const uint8_t ADXL_RES = 4;

const float   HIT_TIME_WINDOW = 500;
const float   TAP_THRESH      = 2.0;
const float   TAP_DUR         = 30;


}; // namespace Config
 

#endif // !__CONFIG_H
