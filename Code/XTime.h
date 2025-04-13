#ifndef XTIME_H
#define XTIME_H
/*
		时间类
制作定时器，设置画面FPS，获取DeltaTime
*/
#include <chrono>
#include <thread>
#include <Windows.h>
#include <iostream>

using namespace std::chrono;

class XTime
{
	friend int main();
private:
	XTime();
	static XTime* pXtime_obj_;
public:
	inline static XTime* getTimeObj() {
		if (pXtime_obj_ == nullptr) pXtime_obj_ = new XTime();
		return pXtime_obj_;
	}

	//计算FPS
	inline void fpsSampling() {
		dTotal_time_FPS_ += dDeltaTime_;
		dTotal_fps_++;
		if (dTotal_time_FPS_ >= 1.0) {
			dFPS_ = dTotal_fps_;
			dTotal_time_FPS_ = 0;
			dTotal_fps_ = 0;
		}
	}

	//游戏开始到现在的时间
	static inline float getTime() {
		duration<float> time = duration_cast<duration<float>>(steady_clock::now() - pXtime_obj_->start_time_);
		return time.count();
	}

private:
	//开始渲染
	inline void renderBegin() {
		dStay_time_ = steady_clock::now();
	}

	//结束渲染
	inline void renderEnd() {
		dEnd_time_ = steady_clock::now();
	}

	//限制帧数
	inline void limitFPS() {
		duration<double> &&deltaTime = duration_cast<duration<double>>(dEnd_time_ - dStay_time_);
		dDeltaTime_ = deltaTime.count();
		dUndormancy_DeltaTime_ = dDeltaTime_;
		if (dDeltaTime_ < dLowestTime_) dLowestTime_ = dDeltaTime_;
		if (dDeltaTime_ > dHighestTime_) dHighestTime_ = dDeltaTime_;
		if (dDeltaTime_ <= dTarget_FPS_time_) {
			std::this_thread::sleep_for(std::chrono::microseconds((long long)((dTarget_FPS_time_ - dDeltaTime_) * 1000000)));
			dDeltaTime_ = dTarget_FPS_time_;
		}
	}

	//根据FPS获取线程休眠时间
	inline double getSleepTimeWithFPS() const {
		return dTarget_FPS_time_ * 1000;
	}

public:

	//获取两帧之间的时间
	static inline double getDeltaTime(){
		return pXtime_obj_->dDeltaTime_;
	}

	//获取两帧之间的目标时间
	inline double getUndormancyDeltaTime() const {
		return dUndormancy_DeltaTime_;
	}

	//设置最大帧数
	inline void setMaxFPS(float FPS) {
		dMax_FPS_ = FPS;
		dTarget_FPS_time_ = 1.0 / dMax_FPS_;
	}
	~XTime();
public:
	double							dLowestTime_;			//渲染一帧所用的最少时间
	double							dHighestTime_;			//渲染一帧所用的最多时间

	double							dFPS_;					//帧数对外接口
	double							dMax_FPS_;				//用户设置的最大帧数

private:
	double							dDeltaTime_;			//两针之间的时间：逻辑+渲染+休眠
	double							dUndormancy_DeltaTime_; //除去休眠的时间：逻辑+渲染

	double							dTarget_FPS_time_;		//理想渲染时间：逻辑+渲染+休眠
	double							dTotal_time_FPS_;		//计算1s内帧数的当前总时间
	double							dTotal_fps_;			//计算时1s内的总帧数

	steady_clock::time_point		start_time_;			//游戏开始时间
	steady_clock::time_point		dStay_time_;			//开始时间；逻辑+渲染的计算
	steady_clock::time_point		dEnd_time_;				//结束时间；逻辑+渲染的计算
};

#endif