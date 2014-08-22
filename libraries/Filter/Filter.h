/*------------------------------------------------------------------------------
Class:
	Filter

Responsibilities:
	- Take in data from AMU and spit out a single number representing the
	  current best estimate of swing's angle.

Collaborators:
	- Input comes from AMU
	- Output goes to physics engine (Swing class).
------------------------------------------------------------------------------*/
#ifndef Filter_H
#define Filter_H
#include <math.h>
#include <Arduino.h>
// #if (ARDUINO >= 100)
//  #include <Arduino.h>
// #else
//  #include <WProgram.h>
//  #include <pins_arduino.h>
// #endif

class Filter {
	public:
		Filter(void);

		float
			getSwingAngle(void);
		void
			update(float measurement[3]);

	private:
		const float
			timeScale;
		float
			now,
			lastTime,
			timeDelta,
			thetaBestGuess,
			pitchOffset,
			sumTheta,
			ticks,
			maxTicks;
};
#endif