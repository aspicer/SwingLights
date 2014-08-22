#include "Diameter.h"
// ----------------------------------------
//      Begin Diameter Definitions
// ----------------------------------------
Diameter::Diameter(){
	hsvStrip = HsvStrip;
	value = 255; // default to bright!
	angle = 0;
}
void Diameter::rotateBy(int a) {
	angle += a;
}
void Diameter::rotateTo(int a) {
	angle = a;
}
void Diameter::changeValueBy(int value){
	value += value;
}
void Diameter::setValueTo(int value){
	value = value;
}
