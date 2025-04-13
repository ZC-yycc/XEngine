#include "XTime.h"

XTime* XTime::pXtime_obj_ = nullptr;

XTime::XTime() {
	srand(time(0));
	dTotal_time_FPS_ = 0.0;
	dTotal_fps_ = 0.0;
	dMax_FPS_ = 60.0;
	dTarget_FPS_time_ = 1.0/dMax_FPS_;
	dFPS_ = 0;
	start_time_ = steady_clock::now();
	dDeltaTime_ = 0;
	dUndormancy_DeltaTime_ = 0;
	dLowestTime_ = 2;
	dHighestTime_ = -1;
}

XTime::~XTime()
{
}
