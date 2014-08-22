#include <WProgram.h>
#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Swing.h>
#include <stdint.h>
#include <math.h>

typedef struct RgbColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}RgbColor;

typedef struct HsvColor{
    unsigned char h;
    unsigned char s;
    unsigned char v;
}HsvColor;