//#include <HSV.h>
#include "globals.h"

#ifndef Diameter_H
#define Diameter_H

class Diameter : public HSV {
	public:
		// Diameter(); // Diameter in Hue / Sat x-section w/ fixed V
		void rotateBy(int a);
		void rotateTo(int a);
		void changeValueBy(int value);
		void setValueTo(int value);
	private:
		int value; // Value
		int angle; // Angle
};
#endif