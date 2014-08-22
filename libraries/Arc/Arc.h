#include <HSV.h>
#include "globals.h"

#ifndef Arc_H
#define Arc_H

class Arc : public HSV {
	public:
		Arc();
		void rotateBy(int a);
		void rotateTo(int a);
		void changeSpanBy(int a);
		void setSpanTo(int a);
		void changeSaturationBy(int deltaS);
		void setSaturationTo(unsigned char s);
	private:
		int saturation; // Saturation (radius)
		int angle; // Angle where arc begins.
		int span; // int between 0 and 255. 0 is all one color. 255 is full 360 degrees.
};
#endif