#include <Routine.h>
// These four includes are strangly required
// http://stackoverflow.com/questions/21418036/iso-c-forbids-declaration-of-vector-with-no-type
#include <Wire.h>
#include <Swing.h>
#include <Adafruit_NeoPixel.h>
#include <FreeSixIMU.h>   // library for IMU
#include <myCommon.h>

class ContractingRainbow : public Routine {
public:
  int counter;
  float maxTE;
  ContractingRainbow() {
    counter = 0;
    maxTE = 0;
  }
  void loop() {
    // This starts with a really spread out hsv rainbow that is slowly cycling through the colors, like swinglight
    // As TE goes up, the rainbow cycles faster and faster and gets tighter and tighter
    int te = SWING->getTE();
    if (te > maxTE) maxTE = te;

    // want to make i increment by more if te is higher

    float percentage = 100*te/maxTE;
    // if percentage is 100, 5
    // if percantage is 0, 0
    int multiplier = ((int)percentage) / 20;
    //Serial.println(te);
    //Serial.println(maxTE);
    Serial.println(multiplier);
    Serial.println();
    counter += 1 + multiplier;

    HsvColor hsvcolor;
    for (int i = 0; i < 240; i++) {
      hsvcolor.v = 255;
      hsvcolor.s = 255;
      hsvcolor.h = counter + (i * 255/239)%256;
      RgbColor rgb = HsvToRgb(hsvcolor);
      setStripColor(i, rgb);
    }
  };
};

int main() {
  Routine *routine = new ContractingRainbow();
  routine->start();
  return 0;
}

