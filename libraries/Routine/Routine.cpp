#include "Routine.h"
#include <WProgram.h>
#include <FreeSixIMU.h>   // library for IMU
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Swing.h>
#include <stdint.h>
#include <math.h>

const int PIXELS_PER_STRIP=240;
#define PIN 6

Routine::Routine() {
  Serial.println("ZZZBADZZZ");
  SWING = new Swing(SWING_LENGTH);
  SIXDOF = new FreeSixIMU();
  STRIP = new Adafruit_NeoPixel(PIXELS_PER_STRIP, PIN, NEO_GRB + NEO_KHZ800);
}

Routine::Routine(Swing *swing, FreeSixIMU *sixdof, Adafruit_NeoPixel *strip) {
  SWING = swing;
  SIXDOF = sixdof;
  STRIP = strip;
}

void Routine::loop() {
  for (int i = 0; i < 240; i++) {
    STRIP->setPixelColor(i, STRIP->Color(255,0,0));
  }
}

void Routine::performLoop() {
  updateAngle();
  loop();
  STRIP->show();
}

void Routine::setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(5);
  SIXDOF->init(); //begin the IMU
  delay(5);
  STRIP->begin();
  STRIP->show();
}

void Routine::start() {
  init();
  setup();
  while (1) {
    performLoop();
  }
}

void Routine::setStripColor(int i, RgbColor rgb) {
  STRIP->setPixelColor(i, STRIP->Color(rgb.r, rgb.g, rgb.b));
}

void Routine::updateAngle() {
    float angle;
    SIXDOF->getYawPitchRoll(ypr);
    angle = ypr[1] * sin(PITCH_ROLL_OFFSET*M_PI/180) + ypr[2] * cos(PITCH_ROLL_OFFSET*M_PI/180);
    SWING->updatePhysics(angle);
};