#include "globals.h"
#include <LightingModel.h>
//class LightingModel;

#ifndef HSV_H
#define HSV_H

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



