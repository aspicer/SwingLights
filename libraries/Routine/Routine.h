#include <myCommon.h>
#include <WProgram.h>
#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Swing.h>
#include <stdint.h>
#include <math.h>

#ifndef Routine_H
#define Routine_H

class Routine 
{
private:
    static const float SWING_LENGTH = 3.3;
    static const float PITCH_ROLL_OFFSET = 75.0;
    float ypr[3]; // yaw pitch roll
    void updateAngle();
protected:
    Swing *SWING;
    FreeSixIMU *SIXDOF;
    Adafruit_NeoPixel *STRIP;
public:
    Routine();
    void loop();
    void setup();
    void start();
};
#endif