#ifndef __PALETTE_H
#define __PALETTE_H


#include <FastLED.h>


__attribute__((always_inline))
inline CRGB
WS2812GRB(uint32_t colorCode) {
	CRGB color(colorCode);
	CRGB newColor;

	newColor.r = color.g;
	newColor.g = color.b;
	newColor.b = color.r;
	
	return newColor;
}


namespace Pal {

	
const CRGB
    BG            = WS2812GRB(0x21035C),
	SPARKLE       = WS2812GRB(0xDB67F0),
	SPARKLE_TO_BG = WS2812GRB(0xFFFFFF-0x204010),

	HIT_SPARKLE = 0x0B8000,
	HIT_TAIL    = 0xFFFFFF;

	
}; // namespace Pal
	

#endif // !__PALETTE_H
