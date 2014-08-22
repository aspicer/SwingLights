#include "HSV.h"
// ----------------------------------------
//      Begin HSV Definitions
// ----------------------------------------
HSV::HSV(){
}

void HSV::update(){
	setStrip();
}
void HSV::setup(){
	// HsvColor black;
	// black.h = 0;
	// black.s = 0;
	// black.v = 0;
	for (uint8_t i = 0; i < 240; i++){
		hsvStrip[i].h = 0;
        hsvStrip[i].s = 0;
        hsvStrip[i].v = 0;
	}
}
void HSV::setStrip(){
	RgbColor rgb;
	for (uint8_t i = 0; i < 240; i++){
		rgb = HsvToRgb(hsvStrip[i]);
		STRIP.setPixelColor(i, Color(rgb.r, rgb.g, rgb.b));
	}
}
void HSV::HsvToRgb(HsvColor) {
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6;

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}
