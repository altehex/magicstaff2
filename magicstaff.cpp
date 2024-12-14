#include "magicstaff.h"


#include <FastLED.h>
#include <util/delay.h>

#include "adxl.h"
#include "palette.h"


namespace MagicStaff {


bool (* fx)(void) = standby_fx_2;

CRGB leds[Config::LED_COUNT];

volatile bool intOccured = false;

	
void
int_notify(void) {
	intOccured = true;
}


void
test_fx(void)
{
	leds[0] = CRGB::Red;
	for (int i = 1; i < Config::LED_COUNT; ++i) {
		leds[i-1] = CRGB::Black;
		leds[i] = CRGB::Red;
		FastLED.show();
		_delay_ms(250);
	}
}
	

void
standby_init(void) {
	FastLED.showColor(Pal::BG);
}
	

bool
standby_fx(void)
{
	static const uint8_t FRAME_COUNT = 1;
	static uint8_t frame = FRAME_COUNT;
	uint8_t led;

	fadeUsingColor(
		leds,
		Config::LED_COUNT,
		Pal::SPARKLE_TO_BG
	);
	
	if (--frame == 0) {
		frame = FRAME_COUNT;

		led = random8(Config::LED_COUNT);
		leds[led] = Pal::SPARKLE;
	}

	_delay_ms(25);
	
	return false;
}


bool
standby_fx_2(void)
{
	// fadeToBlackBy(leds, Config::LED_COUNT, 4);
	
	return false;
}


bool
hit_fx(void)
{
	static const uint8_t FRAME_COUNT = Config::LED_COUNT;
	static uint8_t frame = 0;
	uint8_t i = 0;
	
	fadeToBlackBy(leds, Config::LED_COUNT, 24);

	if ((++frame)+10 > FRAME_COUNT) {
		frame = 0;
		return true;
	};

	// switch ((frame+10)%) {
	// 	case 0: leds[frame+i++] = 0x0B8000;
	// 	case 1: leds[frame+i++] = 0x198C0E;
	//     case 2: leds[frame+i++] = 0x29991F;
	//     case 3: leds[frame+i++] = 0x3BA632;
	//     case 4: leds[frame+i++] = 0x50B347;
	//     case 5: leds[frame+i++] = 0x68BF60;
	//     case 6: leds[frame+i++] = 0x81CC7A;
	//     case 7: leds[frame+i++] = 0x9DD998;
	//     case 8: leds[frame+i++] = 0xB8E6BB;
	//     case 9: leds[frame+i++] = 0xFFFFFF;
	// }
	
	leds[frame]                  = 0x0B8000;
	leds[(frame+1)%FRAME_COUNT]  = 0x198C0E;
	leds[(frame+2)%FRAME_COUNT]  = 0x29991F;
	leds[(frame+3)%FRAME_COUNT]  = 0x3BA632;
	leds[(frame+4)%FRAME_COUNT]  = 0x50B347;
	leds[(frame+5)%FRAME_COUNT]  = 0x68BF60;
	leds[(frame+6)%FRAME_COUNT]  = 0x81CC7A;
	leds[(frame+7)%FRAME_COUNT]  = 0x9DD998;
	leds[(frame+8)%FRAME_COUNT]  = 0xB8E6BB;
	leds[(frame+9)%FRAME_COUNT]  = 0xDAF2DA;
	leds[(frame+10)%FRAME_COUNT] = 0xFFFFFF;

	_delay_ms(50);
	
	return false;
}


bool
hit_fx_2(void)
{
	static const uint8_t FRAME_COUNT = Config::LED_COUNT*2;
	static uint8_t led = 0,
		           frame = 0,
		           colorIndex = 0;
	static CRGB colors[2] = { WS2812GRB(CRGB::Blue), CRGB::Black };
	
	if (led == Config::LED_COUNT) {
		led = 0;
		colorIndex ^= 1;
	}

	if (frame == FRAME_COUNT) {
		frame = 0;
		return true;
	}

	leds[led++] = colors[colorIndex];

	++frame;

	_delay_ms(25);
	
	return false;
}
	

bool
hit3times_fx(void)
{
	static const uint8_t FRAME_COUNT = 100,
		                 PHASE_COUNT = 7;
	static uint8_t frame = FRAME_COUNT,
		           p = 0,
		           hue = 0;

	if (--frame == 0) {
		frame = FRAME_COUNT;
		return true;
	}

	if (++p == PHASE_COUNT)
		p = 0;
	 
	for (int i = 0; i < Config::LED_COUNT; i += PHASE_COUNT) {
		leds[i+p] = CRGB::Black;
		leds[i+(p+1)%6] = CHSV(++hue, 160, 85);
		leds[i+(p+2)%6] = CHSV(++hue, 120, 170);
		leds[i+(p+3)%6] = CHSV(++hue, 100, 255);
		leds[i+(p+4)%6] = CHSV(++hue, 120, 170);
		if (i < 42) {
			leds[i+(p+5)%6] = CHSV(++hue, 160, 85);
			leds[i+(p+6)%7] = CRGB::Black;
		}
	}

	_delay_ms(50);
	
	return false;	
}


bool
hit3times_fx_2(void)
{
	static const uint8_t FRAME_COUNT = 1000;
	static uint8_t frame = FRAME_COUNT;

	if (--frame == 0) {
		frame = FRAME_COUNT;
		return true;
	}

	return standby_fx();
}
	

bool
shake_fx(void)
{

	return true;	
}


}; // namespace MagicStaff
