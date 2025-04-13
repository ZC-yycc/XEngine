#ifndef INTERFACELIB_H
#define INTERFACELIB_H
#include <functional>
#include "XArray.h"
#include <memory>
/*
		�ӿڿ�
XBehaviorBase���ӿڿ���࣬����������������ʾ����XObject�̳�
XBehaviorRun����Ⱦʱ����µĺ�������XActor�̳�
XBehaviorFixedRun���̶�ʱ����µĺ�������XActor�̳�
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
