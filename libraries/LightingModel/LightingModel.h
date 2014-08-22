//#include "globals.h"

#ifndef LightingModel_H
#define LightingModel_H

class LightingModel {
	public:
		LightingModel();
		virtual void setup(); // called when model is first loaded
		virtual void update(); // this function will be called to update your model.
		int getTimeElapsed(); // total time in this model in milliseconds

	private:
		int startTime;
		int currentTime;
};
#endif