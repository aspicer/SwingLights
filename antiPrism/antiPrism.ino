#include <myCommon.h>
#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Swing.h>
#include <stdint.h>
#include <math.h>

float SWING_LENGTH = 3.3;
FreeSixIMU SIXDOF = FreeSixIMU();
float PITCH_ROLL_OFFSET = 124.7;
Swing SWING = Swing(SWING_LENGTH);
const int PIXELS_PER_STRIP=240;
#define PIN 6
Adafruit_NeoPixel STRIP = Adafruit_NeoPixel(PIXELS_PER_STRIP, PIN, NEO_GRB + NEO_KHZ800);

bool DEBUG=true;

void setup() {
	setupIMU();
	setupStrip();
}

float ypr[3]; // yaw pitch roll

void setStripColor(int i, RgbColor rgb) {
	STRIP.setPixelColor(i, STRIP.Color(rgb.r, rgb.g, rgb.b));
}

int counter = 0;
RgbColor red={255,0,0};
RgbColor ora={255,140,0};
RgbColor yel={255,255,0};
RgbColor gre={0,255,0};
RgbColor blu={0,0,255};
RgbColor vio={238,130,238};
RgbColor white = {255,255,255};
float thetaMax = 10.0;
RgbColor colors[6] = {red, ora, yel, gre, blu, vio};
RgbColor color;
int pixelsPerCycle;
float angle;
void loop() {
	updateAngle();
	angle = SWING.getTheta() / 3;
        Serial.println(angle);
	float pixelsPerColor = thetaMax / abs(1 + angle);
        //Serial.println(pixelsPerColor);
	pixelsPerCycle = (int) 6 * pixelsPerColor;
        //Serial.println(pixelsPerCycle);
        
	for (int i = 0; i<240; i++){
                if (pixelsPerColor <= 1) {
                  setStripColor(i,white);
                }
                else{
  		  int x = (int) ((i % pixelsPerCycle) / pixelsPerColor);
  		  color = colors[x];
  		  setStripColor(i, color);
                }
	}
	STRIP.show();
}
void updateAngle(){
	float angle;
	SIXDOF.getYawPitchRoll(ypr);
    angle = ypr[1] * sin(PITCH_ROLL_OFFSET*M_PI/180) + ypr[2] * cos(PITCH_ROLL_OFFSET*M_PI/180);
	SWING.updatePhysics(angle);
}
void setupIMU() {
	Serial.begin(9600);
	Wire.begin();
	delay(5);
	SIXDOF.init(); //begin the IMU
	delay(5);
}
void setupStrip() {
	STRIP.begin();
	STRIP.show();
}

