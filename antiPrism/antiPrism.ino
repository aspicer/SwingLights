#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Swing.h>
#include <stdint.h>
#include <math.h>
#include <Routine.h>

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

float counter = 1200.0;
//RgbColor red={235,0,0};
//RgbColor ora={255,110,0};
//RgbColor yel={200,232,0};
//RgbColor gre={0,235,0};
//RgbColor blu={0,0,255};
//RgbColor vio={168,0,255};
//RgbColor white = {255,255,255};
RgbColor red={255,0,0};
RgbColor ora={255,255,0};
RgbColor yel={0,255,255};
RgbColor gre={0,255,0};
RgbColor blu={0,0,255};
RgbColor vio={255,0,255};
RgbColor white = {255,255,255};
int thetaMax = 50;
RgbColor colors[6] = {vio, blu, gre, yel, ora, red};
RgbColor color;
int pixelsPerCycle;
float angle;
float TE;
int counterINT;
int dir = 1;
void loop() {
	updateAngle();
	counter += dir*min(max(SWING.getTE(), 1.2), 8.0);
        counterINT = (int)counter;
	//float pixelsPerColor = 12* thetaMax / (thetaMax + (counterINT % thetaMax));
        for (int j=0; j<counterINT / 600; j++){
          dir = dir*-1;
        }
        float pixelsPerColor = 40.0*(float)((counterINT % 600) + 25)/625.0;
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

