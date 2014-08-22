#include "Arduino.h"
#include "Filter.h"
#include "MatrixMath.h"

float X[4][1];
float Y[2][1];
float Q[4][4];
float R[2][2];
float S[4][4];
float PHI[4][4];
float M[2][4];

Filter::Filter() :
	timeScale(300)  // in seconds. Needs to be big enough to capture a couple swings.
	{
	thetaBestGuess   = 0;
	now = micros() / 1000000;
	lastTime = 0.0;
	timeDelta = 0.000001;
	sumTheta = 0;
	ticks = 0;
	maxTicks = timeScale / timeDelta;
}

// begin public methods
float Filter::getSwingAngle() {
	return thetaBestGuess;
}
// measurement is yaw, pitch, roll
void Filter::update(float measurement[3]) {
	float pitch = measurement[1];
	float roll = measurement[2];
	Y[0][0] = pitch;
	Y[1][0] = roll;
	// X Guess
	float guessX[4][1];
	Matrix.Multiply((float*)PHI, (float*)X, 4, 4, 1, (float*)guessX);
	// S Guess
	float m1[4][4];
	float phiT[4][4];
	float m2[4][4];
	float guessS[4][4];
	Matrix.Multiply((float*)PHI, (float*)S, 4, 4, 4, (float*)m1);
	Matrix.Transpose((float*)PHI, 4, 4, (float*)phiT);
	Matrix.Multiply((float*)m1, (float*)phiT, 4, 4, 4, (float*)m2);
	Matrix.Add((float*)m2, (float*)Q, 4, 4, (float*)guessS);
	// K T
	float m3[2][4];
	float m4[2][2];
	float MT[4][2];
	float m5[2][2];
	float m6[4][2];
	float K[4][2];
	Matrix.Transpose((float*)M, 4 , 2, (float*)MT);
	Matrix.Multiply((float*)M, (float*)guessS, 4, 2, 4, (float*)m3);
	Matrix.Multiply((float*)m3, (float*)MT, 2, 4, 2, (float*)m4);
	Matrix.Add((float*)m4, (float*)R, 2, 2, (float*)m5);
	Matrix.Invert((float*)m5, 2);
	Matrix.Multiply((float*)guessS, (float*)MT, 4, 4, 2, (float*)m6);
	Matrix.Multiply((float*)m6, (float*)m5, 4, 2, 2, (float*)K);
	// X
	float n1[2][1];
	float n2[2][1];
	float n3[4][1];
	Matrix.Multiply((float*)M, (float*)guessX, 2, 4, 1, (float*)n1);
	Matrix.Subtract((float*)Y, (float*)n1, 2, 1, (float*)n2);
	Matrix.Multiply((float*)K, (float*)n2, 4, 2, 1, (float*)n3);
	Matrix.Add((float*)guessX, (float*)n3, 4, 1, (float*)X);
	// S
	float n4[4][4];
	float n5[4][4];
	float I[4][4] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	Matrix.Multiply((float*)K, (float*)M, 4, 2, 4, (float*)n4);
	Matrix.Subtract((float*)I, (float*)n4, 4, 4, (float*)n5);
	Matrix.Multiply((float*)n5, (float*)guessS, 4, 4, 4, (float*)S);








}



