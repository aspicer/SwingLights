#include <Routine.h>
// These four includes are strangly required
// http://stackoverflow.com/questions/21418036/iso-c-forbids-declaration-of-vector-with-no-type
#include <Wire.h>
#include <Swing.h>
#include <Adafruit_NeoPixel.h>
#include <FreeSixIMU.h>   // library for IMU

class ContractingRainbow : public Routine {
  void loop() {
    for (int i = 0; i < 240; i++) {
      STRIP->setPixelColor(i, STRIP->Color(0,0,255));
    }
  };
};

int main() {
  Routine *routine = new ContractingRainbow();
  routine->start();
  return 0;
}




