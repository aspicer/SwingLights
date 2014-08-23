#include <Routine.h>
// These four includes are strangly required
// http://stackoverflow.com/questions/21418036/iso-c-forbids-declaration-of-vector-with-no-type
#include <Wire.h>
#include <Swing.h>
#include <Adafruit_NeoPixel.h>
#include <FreeSixIMU.h>   // library for IMU
#include <myCommon.h>

class AntiPrism : public Routine {
public:
  float counter;
  RgbColor red, ora, yel, gre, blu, vio, white;
  int thetaMax;
  RgbColor colors[6];
  RgbColor color;
  int pixelsPerCycle;
  float angle;
  float TE;
  int counterINT;
  int dir;
  AntiPrism() {
    counter = 1200.0;
    red=RgbColor(255,0,0);
    ora=RgbColor(255,255,0);
    yel=RgbColor(0,255,255);
    gre=RgbColor(0,255,0);
    blu=RgbColor(0,0,255);
    vio=RgbColor(255,0,255);
    white = RgbColor(255,255,255);
    thetaMax = 50;
    colors[0] = vio; colors[1] = blu; colors[2] = gre; colors[3] = yel; colors[4] = ora, colors[5] = red;
    dir = 1;
  }
  AntiPrism(Swing *swing, FreeSixIMU *sixdof, Adafruit_NeoPixel *strip) : Routine(swing, sixdof, strip) {
    AntiPrism();
  }
  void loop() {
    counter += dir*min(max(SWING->getTE(), 1.2), 8.0);
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
  };
};

int main() {
  Routine *routine = new AntiPrism();
  routine->start();
  return 0;
}


