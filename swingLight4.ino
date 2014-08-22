
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
float SWING_LENGTH = 3.3;
FreeSixIMU SIXDOF = FreeSixIMU();
float PITCH_ROLL_OFFSET = 75.0;
Swing SWING = Swing(SWING_LENGTH);
const int PIXELS_PER_STRIP=240;
#define PIN 6
Adafruit_NeoPixel STRIP = Adafruit_NeoPixel(PIXELS_PER_STRIP, PIN, NEO_GRB + NEO_KHZ800);

bool DEBUG=true;


// #include <HSV.h>
// #include <Diameter.h>

// timing constants
int ANG_TIME_DELAY=20; // milliseconds
int ANG_LAST_TIME;
int LED_TIME_DELAY=20; // milliseconds
int LED_LAST_TIME;

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

class HSV { //: public LightingModel {
	public:
		HSV(){};
		HsvColor hsvStrip[240];
		void update(){
			STRIP.setPixelColor(120, STRIP.Color(0,0,255));
			STRIP.show();
		}
		void setup(){
			for (uint8_t i = 0; i < 240; i++){
				hsvStrip[i].h = 0;
		        hsvStrip[i].s = 0;
		        hsvStrip[i].v = 0;
			}
		}
		RgbColor HsvToRgb(HsvColor hsv){
		    RgbColor rgb;
		    unsigned char region, remainder, p, q, t;

		    if (hsv.s == 0)
		    {
		        rgb.r = hsv.v;
		        rgb.g = hsv.v;
		        rgb.b = hsv.v;
		        return rgb;
		    }

		    region = hsv.h / 43;
		    remainder = (hsv.h - (region * 43)) * 6;

		    p = (hsv.v * (255 - hsv.s)) >> 8;
		    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
		    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

		    switch (region)
		    {
		        case 0:
		            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
		            break;
		        case 1:
		            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
		            break;
		        case 2:
		            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
		            break;
		        case 3:
		            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
		            break;
		        case 4:
		            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
		            break;
		        default:
		            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
		            break;
		    }

		    return rgb;
		};
		//HsvColor RgbToHsv(RgbColor rgb);
		void setStrip(){
			for (uint8_t i = 0; i<240; i++){
				STRIP.setPixelColor(i, STRIP.Color(255,0,0));
			}

			// RgbColor rgb;
			// for (uint8_t i = 0; i < 240; i++){
			// 	rgb = HsvToRgb(hsvStrip[i]);
			// 	STRIP.setPixelColor(i, STRIP.Color(rgb.r, rgb.g, rgb.b));
			// }
		};
};

void setup() {
	setupIMU();
	setupStrip();
}

float ypr[3]; // yaw pitch roll

HSV *hsv = new HSV();

void setStripColor(int i, RgbColor rgb) {
	STRIP.setPixelColor(i, STRIP.Color(rgb.r, rgb.g, rgb.b));
}

int counter = 0;
void loop() {
	updateAngle();

	counter = counter + 1;

	int theta = (int) (SWING.getTheta() + 90);
	// Serial.println(theta);
	HsvColor hsvcolor;
	int base = counter;
	for (int i = 0; i < 240; i++) {
		hsvcolor.v = 255;
		hsvcolor.s = 255;
		hsvcolor.h = ((base + i) * 255/239)%256;
		RgbColor rgb = hsv->HsvToRgb(hsvcolor);
		if (hsvcolor.h > 120 && hsvcolor.h < 150) {
			rgb.r = abs(hsvcolor.h - 135);
			rgb.g = abs(hsvcolor.h - 135) * 5;
			rgb.b = abs(hsvcolor.h - 135) * 5;
		}
		setStripColor(i, rgb);
	}
	// theta = (theta + 180) % 360;
	// for (int i = 120; i < 240; i++) {
	// 	hsvcolor.v = 255;
	// 	hsvcolor.s = i * i / 255;
	// 	hsvcolor.h = counter;
	// 	RgbColor rgb = hsv->HsvToRgb(hsvcolor);
	// 	STRIP.setPixelColor(i, STRIP.Color(rgb.r, rgb.g, rgb.b));
	// }
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
