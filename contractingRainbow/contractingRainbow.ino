#include <Routine.h>
// These four includes are strangly required
// http://stackoverflow.com/questions/21418036/iso-c-forbids-declaration-of-vector-with-no-type
#include <Wire.h>
#include <Swing.h>
#include <Adafruit_NeoPixel.h>
#include <FreeSixIMU.h>   // library for IMU

RgbColor HsvToRgb(HsvColor hsv) {
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
}

class ContractingRainbow : public Routine {
public:
  ContractingRainbow() {
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
  Routine *routine = new ContractingRainbow();
  routine->start();
  return 0;
}







