#include <Adafruit_NeoPixel.h>
#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Swing.h>
#include <LightingModel.h>

#ifndef globals_H
#define globals_H

// class LightingModel;
// class FreeSixIMU;
// class Swing;
// class Adafruit_NeoPixel;

extern int PIXELS_PER_STRIP;
extern int PIN;
extern float SWING_LENGTH;
extern float PITCH_ROLL_OFFSET;
extern FreeSixIMU SIXDOF; // Set the FreeSixIMU object
extern Swing SWING;
extern Adafruit_NeoPixel STRIP;

#endif