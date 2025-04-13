#ifndef XTIME_H
#define XTIME_H
/*
		ʱ����
������ʱ�������û���FPS����ȡDeltaTime
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

	//����FPS
	inline void fpsSampling() {
		dTotal_time_FPS_ += dDeltaTime_;
		dTotal_fps_++;
		if (dTotal_time_FPS_ >= 1.0) {
			dFPS_ = dTotal_fps_;
			dTotal_time_FPS_ = 0;
			dTotal_fps_ = 0;
		}
	}

	//��Ϸ��ʼ�����ڵ�ʱ��
	static inline float getTime() {
		duration<float> time = duration_cast<duration<float>>(steady_clock::now() - pXtime_obj_->start_time_);
		return time.count();
	}

private:
	//��ʼ��Ⱦ
	inline void renderBegin() {
		dStay_time_ = steady_clock::now();
	}

	//������Ⱦ
	inline void renderEnd() {
		dEnd_time_ = steady_clock::now();
	}

	//����֡��
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

	//����FPS��ȡ�߳�����ʱ��
	inline double getSleepTimeWithFPS() const {
		return dTarget_FPS_time_ * 1000;
	}

public:

	//��ȡ��֮֡���ʱ��
	static inline double getDeltaTime(){
		return pXtime_obj_->dDeltaTime_;
	}

	//��ȡ��֮֡���Ŀ��ʱ��
	inline double getUndormancyDeltaTime() const {
		return dUndormancy_DeltaTime_;
	}

	//�������֡��
	inline void setMaxFPS(float FPS) {
		dMax_FPS_ = FPS;
		dTarget_FPS_time_ = 1.0 / dMax_FPS_;
	}
	~XTime();
public:
	double							dLowestTime_;			//��Ⱦһ֡���õ�����ʱ��
	double							dHighestTime_;			//��Ⱦһ֡���õ����ʱ��

	double							dFPS_;					//֡������ӿ�
	double							dMax_FPS_;				//�û����õ����֡��

private:
	double							dDeltaTime_;			//����֮���ʱ�䣺�߼�+��Ⱦ+����
	double							dUndormancy_DeltaTime_; //��ȥ���ߵ�ʱ�䣺�߼�+��Ⱦ

	double							dTarget_FPS_time_;		//������Ⱦʱ�䣺�߼�+��Ⱦ+����
	double							dTotal_time_FPS_;		//����1s��֡���ĵ�ǰ��ʱ��
	double							dTotal_fps_;			//����ʱ1s�ڵ���֡��

	steady_clock::time_point		start_time_;			//��Ϸ��ʼʱ��
	steady_clock::time_point		dStay_time_;			//��ʼʱ�䣻�߼�+��Ⱦ�ļ���
	steady_clock::time_point		dEnd_time_;				//����ʱ�䣻�߼�+��Ⱦ�ļ���
};

#endif