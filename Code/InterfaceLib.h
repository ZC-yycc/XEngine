#ifndef INTERFACELIB_H
#define INTERFACELIB_H
#include <functional>
#include "XArray.h"
#include <memory>
/*
		接口库
XBehaviorBase：接口库基类，负责最基础的组件显示，由XObject继承
XBehaviorRun：渲染时间更新的函数，由XActor继承
XBehaviorFixedRun：固定时间更新的函数，由XActor继承
*/
class XObject;

struct XBehaviorBase
{
	virtual void begin();
	virtual void show();
};

struct XBehaviorRun : public XBehaviorBase
{
	virtual void run();
};

struct XGUIBehaviorBase
{
	XKeyVector<size_t, std::function<void()>> gui_comps_show_kv_;
	XKeyVector<size_t, std::function<void()>> gui_comps_run_kv_;
	void showCanvas();
	void runCanvas();
	virtual void run() = 0;
};
#endif
