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

typedef struct RgbColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    RgbColor() {}
    RgbColor(unsigned char _r, unsigned char _g, unsigned char _b) {
        r = _r;
        g = _g;
        b = _b;
    }
}RgbColor;

typedef struct HsvColor{
    unsigned char h;
    unsigned char s;
    unsigned char v;
}HsvColor;

class Routine 
{
private:
    static const float SWING_LENGTH = 3.3;
    static const float PITCH_ROLL_OFFSET = 75.0;
    float ypr[3]; // yaw pitch roll
protected:
    Swing *SWING;
    FreeSixIMU *SIXDOF;
    Adafruit_NeoPixel *STRIP;
    void setStripColor(int i, RgbColor rgb);
    void updateAngle();
public:
    Routine();
    Routine(Swing *swing, FreeSixIMU *sixdof, Adafruit_NeoPixel *strip);
    virtual void loop();
    void setup();
    void start();
    void performLoop();
};
#endif