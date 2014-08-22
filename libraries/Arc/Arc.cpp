#include "Arc.h"
// ----------------------------------------
//      Begin Arc Definitions
// ----------------------------------------
Arc::Arc(){
	saturation = 255;
	angle = 0;
	span = 255; // full 360 degrees
}
void Arc::rotateBy(int a) {
	angle += a;
}
void Arc::rotateTo(int a) {
	angle = a;
}
void Arc::changeSpanBy(int a) {
	span += a;
}
void Arc::setSpanTo(int a) {
	span = a;
}
void Arc::changeSaturationBy(int s) {
	saturation += s;
}
void Arc::setSaturationTo(int s) {
	saturation = s;
}