#ifndef __MAGICSTAFF_H
#define __MAGICSTAFF_H


#include <FastLED.h>
#include <util/delay.h>

#include "adxl.h"
#include "config.h"


namespace MagicStaff {
	

void int_notify(void);

void standby_init(void);
	
bool standby_fx(void);
bool standby_fx_2(void);
bool hit_fx(void);
bool hit_fx_2(void);
bool hit3times_fx(void);
bool hit3times_fx_2(void);
bool shake_fx(void);
void test_fx(void);


extern bool (* fx)(void);

extern CRGB leds[Config::LED_COUNT];

extern volatile bool intOccured;


__attribute__((always_inline))
inline void
init(void)
{
	FastLED
		.addLeds<WS2812, Config::LED_PIN, GRB>(leds, Config::LED_COUNT)
		.setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(Config::BRIGHTNESS);

	// test_fx();
	
}


__attribute__((always_inline))	
inline void
handle_int(void)
{
	static unsigned long lastHitTime,
		                 thisHitTime;
	static uint8_t hitCount = 0;
	
	Adxl::get_int_mask();

	Serial.println(Adxl::intMask, BIN);
	
	if (Adxl::intMask & Adxl::SINGLE_TAP) {
		if (hitCount == 3) {
			hitCount = 0;
			fx = hit3times_fx_2;
			goto ret;
		}
		
		fx = hit_fx;
		++hitCount;
		
		goto ret;
	}

	// Потом захерачу
	// get_coords(thisCoords);
	
	// if (Adxl::detect_shake()) {
		
	// }

ret:
	intOccured = false;
	return;
}


__attribute__((always_inline))	
inline void
run(void)
{
	if (fx()) fx = standby_fx_2;

	FastLED.show();

	if (intOccured) handle_int();
	
	// _delay_ms(50);
}
	

}; // namespace MagicStaff
 

#endif // !__MAGICSTAFF_H
