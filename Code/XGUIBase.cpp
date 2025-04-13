#include "XGUIBase.h"
#include "Transform.h"
#include "XEngine.h"

XGUIBase::XGUIBase()
{
	ull_id_ = 0;
	ull_next_component_id_ = 0;
}

XGUIBase::~XGUIBase()
{
}

void XGUIBase::addGUIComponent(XGUIComponentBase* pUIComp)
{
	if(pUIComp->getID() == 0)pUIComp->setID(++ull_next_component_id_);
	gui_comps_show_kv_.pushBack(pUIComp->getID(), [pUIComp]() {if(pUIComp->getState())pUIComp->show(); });
	gui_comps_run_kv_.pushBack(pUIComp->getID(), [pUIComp]() {if (pUIComp->getState())pUIComp->run(); });
}

void XGUIBase::removeGUIComponent(XGUIComponentBase* pUIComp)
{
	gui_comps_show_kv_.erase(pUIComp->getID());
	gui_comps_run_kv_.erase(pUIComp->getID());
}
