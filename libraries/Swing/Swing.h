/*------------------------------------------------------------------------------
Class:
	Swing

Responsibilities:
	- Maintain best current estimate of physical quantities regarding the swing
	  like angular position, angular velocity, total energy, etc...

Collaborators:
	- inputProcessor: the input processor gives a best estimate of swing's current
		angle to the swing class.
	- Lighting Models: Lighting models will request information from this class
	  to inform lighting decisions.
------------------------------------------------------------------------------*/
#ifndef Swing_H
#define Swing_H
#include <math.h>
#include <Arduino.h>

// #if (ARDUINO >= 100)
//  #include <Arduino.h>
// #else
//  #include <WProgram.h>
//  #include <pins_arduino.h>
// #endif

class Swing {
	public:
		// Constructor: length of swing
		Swing(float length);

		void
			updatePhysics(float degreeAngle); // degreeAngle comes from Filter
		float
			getTheta(void),
			getOmega(void),
			getTE(void),
			getCurrentRideTime(void);
		bool
			inUse(void);

	private:
		const int
			g,
			L,
			mass,
			activeEnergyThreshhold,
			timeScale;
		float
			theta,
			lastTheta,
			omega,
			TE,
			now,
			lastTime,
			timeDelta,
			currentRideTimeElapsed,
			currentRideStartTime,
			expSmooth(float previousVal, float measurement),
			toRadians(float degAngle),
			toDegrees(float radAngle);
		void
			updateTime(void),
			updateOmega(void),
			updateTE(void);
		bool
			isSwinging(void),
			wasSwinging;
};
#endif