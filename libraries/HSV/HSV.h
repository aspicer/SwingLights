#include "globals.h"
#include <LightingModel.h>
//class LightingModel;

#ifndef HSV_H
#define HSV_H

//extern Adafruit_NeoPixel STRIP;

typedef struct RgbColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}RgbColor;

typedef struct HsvColor{
    unsigned char h;
    unsigned char s;
    unsigned char v;
}HsvColor;

class HSV { //: public LightingModel {
	public:
		HSV();
		void update();
		void setup();
	private:
		HsvColor hsvStrip[240];
		RgbColor HsvToRgb(HsvColor hsv);
		//HsvColor RgbToHsv(RgbColor rgb);
		void setStrip();
};
#endif



