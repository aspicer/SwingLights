#include "Arduino.h"
#include "Swing.h"

Swing::Swing(float length) :
	// Constants (can be tweaked)
	g(9.8),
	L(length),
	mass(1.0),
	activeEnergyThreshhold(mass * g * 0.01),
	timeScale(1.0 / 20)
	{
	// variables
	theta = 0.0; // radians
	lastTheta = 0.0;
	omega = 0.0; // radiansPerSecond
	TE    = 0.0; // not actual TE since we don't know mass
	now = (float) (micros() / 1000000.0);
	lastTime = 0.0;
	timeDelta= 0.000001;
	currentRideTimeElapsed = 0.0;
	currentRideStartTime = now;
	wasSwinging = false;
}

// -----------------------
// begin private methods
float Swing::toRadians(float degAngle) {return degAngle * M_PI / 180.0;}
float Swing::toDegrees(float radAngle) {return radAngle * 180.0 / M_PI;}
float Swing::expSmooth(float previousVal, float measurement){
	// avoid jerky changes by
	float lastValWeight;
	lastValWeight = 1 - fmin(timeDelta / timeScale, 1);
	return lastValWeight * previousVal + (1 - lastValWeight) * measurement;
}
void Swing::updateTime() {
	lastTime = now;
	now = (float) (micros() / 1000000.0);
	timeDelta = now - lastTime;
	if (isSwinging()) {
		if (! wasSwinging) { // swinging begins
			currentRideStartTime = now;
			currentRideTimeElapsed = 0.0;
			wasSwinging = true;
		}
		else { // swinging continues
			currentRideTimeElapsed = now - currentRideStartTime;
		}
	}
	else {
		if (wasSwinging) { // ride ends
			currentRideTimeElapsed = 0.0;
			wasSwinging = false;
		}
	}
}
void Swing::updateOmega() {
	float deltaTheta, calculatedOmega;
	deltaTheta = theta - lastTheta;
	omega = deltaTheta / timeDelta;
}
void Swing::updateTE() {
	float PE, KE, v;
	PE = mass * g * L * (1 - cos(theta));
	v = omega * L;
	KE = 0.5 * mass * v * v;
	TE = PE + KE;
}
bool Swing::isSwinging() {
	if (TE > activeEnergyThreshhold) {return true;}
	else {return false;}
}
// end private methods

// -----------------------
// begin public methods
void Swing::updatePhysics(float degreeAngle){
	lastTheta = theta;
	theta = toRadians(degreeAngle);
	updateTime();
	updateOmega();
	updateTE();
}
float Swing::getTheta() {
	return toDegrees(theta);
};
float Swing::getOmega() {
	return toDegrees(omega);
}
float Swing::getTE() {
	return TE;
}
float Swing::getCurrentRideTime() {return currentRideTimeElapsed;};
bool Swing::inUse() {return wasSwinging;}
// end public methods
// -----------------------