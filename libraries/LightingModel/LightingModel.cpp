#include "LightingModel.h"

LightingModel::LightingModel(){

	int startTime  = millis();
	int currentTime = startTime;
}
void setup() {};
void update() {};
int LightingModel::getTimeElapsed(){
	return millis() - startTime;
}
