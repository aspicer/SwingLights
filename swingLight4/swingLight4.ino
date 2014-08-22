#include <myCommon.h>
#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Swing.h>
#include <stdint.h>
#include <math.h>
// #include <LightingModel.h>
// #include "globals.h"


bool DEBUG=true;

// #include <HSV.h>
// #include <Diameter.h>

// timing constants
int ANG_TIME_DELAY=20; // milliseconds
int ANG_LAST_TIME;
int LED_TIME_DELAY=20; // milliseconds
int LED_LAST_TIME;

int counter = 0;
void loop() {

	counter = counter + 1;
};

int main() {
	Routine routine = Routine();
	routine.start();
	return 0;
}
