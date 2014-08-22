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



class Routine 
{
private:
    static const float SWING_LENGTH = 3.3;
    static const float PITCH_ROLL_OFFSET = 75.0;
    float ypr[3]; // yaw pitch roll
    void updateAngle() {
        float angle;
        SIXDOF->getYawPitchRoll(ypr);
        angle = ypr[1] * sin(PITCH_ROLL_OFFSET*M_PI/180) + ypr[2] * cos(PITCH_ROLL_OFFSET*M_PI/180);
        SWING->updatePhysics(angle);
    };
protected:
    Swing *SWING;
    FreeSixIMU *SIXDOF;
    Adafruit_NeoPixel *STRIP;
public:
    Routine() {
        SWING = new Swing(SWING_LENGTH);
        SIXDOF = new FreeSixIMU();
        STRIP = new Adafruit_NeoPixel((uint16_t)240, (uint8_t)0, (uint8_t)(NEO_GRB + NEO_KHZ800));
    };
    void loop() {
        for (int i = 0; i < 240; i++) {
            STRIP->setPixelColor(i, STRIP->Color(i,240-i,i));
        }
    };
    void setup() {
        Serial.begin(9600);
        Wire.begin();
        delay(5);
        SIXDOF->init(); //begin the IMU
        delay(5);
        STRIP->begin();
        STRIP->show();
    };
    void start() {
        init();
        setup();
        while (1)
            updateAngle();
            loop();
            STRIP->show();

    };
};