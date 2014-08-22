#include "globals.h"

int PIXELS_PER_STRIP = 240;
int PIN = 6;
float SWING_LENGTH = 3.3;
float PITCH_ROLL_OFFSET = 85.3;
FreeSixIMU SIXDOF = FreeSixIMU(); // Set the FreeSixIMU object
Swing SWING = Swing(SWING_LENGTH);
Adafruit_NeoPixel STRIP = Adafruit_NeoPixel(PIXELS_PER_STRIP, PIN, NEO_GRB + NEO_KHZ800);