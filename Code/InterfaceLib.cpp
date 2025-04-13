#include "InterfaceLib.h"
#include "XEngine.h"
#include "XObject.h"
#include "XGUIBase.h"


void XGUIBehaviorBase::showCanvas()
{
	for (size_t i = 0; i < gui_comps_show_kv_.count(); ++i)
		if (gui_comps_show_kv_[i]) gui_comps_show_kv_[i]();
}

void XGUIBehaviorBase::runCanvas()
{
	for (size_t i = 0; i < gui_comps_run_kv_.count(); ++i)
		if (gui_comps_run_kv_[i]) gui_comps_run_kv_[i]();
	run();
}

void XBehaviorRun::run()
{
}

void XBehaviorBase::begin()
{
}

void XBehaviorBase::show()
{
}
