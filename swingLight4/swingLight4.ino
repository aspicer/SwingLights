#include <Routine.h>
// These four includes are strangly required
// http://stackoverflow.com/questions/21418036/iso-c-forbids-declaration-of-vector-with-no-type
#include <Wire.h>
#include <Swing.h>
#include <Adafruit_NeoPixel.h>
#include <FreeSixIMU.h>   // library for IMU
#include <myCommon.h>

class SwingLight : public Routine {
public:
  SwingLight() {
    counter = 0;
  }
  SwingLight(Swing *swing, FreeSixIMU *sixdof, Adafruit_NeoPixel *strip) : Routine(swing, sixdof, strip) {
    counter = 0;
  }
  int counter;
  void loop() {
    counter = counter + 1;

    int theta = (int) (SWING->getTheta() + 90);
    HsvColor hsvcolor;
    int base = counter;
    for (int i = 0; i < 240; i++) {
      hsvcolor.v = 255;
      hsvcolor.s = 255;
      hsvcolor.h = ((base + i) * 255/239)%256;
      RgbColor rgb = HsvToRgb(hsvcolor);
      if (hsvcolor.h > 120 && hsvcolor.h < 150) {
        rgb.r = abs(hsvcolor.h - 135);
        rgb.g = abs(hsvcolor.h - 135) * 5;
        rgb.b = abs(hsvcolor.h - 135) * 5;
      }
      setStripColor(i, rgb);
    }
  };
};

int main() {
  Routine *routine = new SwingLight();
  routine->start();
  return 0;
}

