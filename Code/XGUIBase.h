#ifndef GUIBASE_H
#define GUIBASE_H
#include "InterfaceLib.h"
#include "XMath.h"
#include "XGUIComponentBase.h"
#include "Transform.h"


class XGUIBase : public XGUIBehaviorBase
{
	friend XGUIComponentBase;
public:
	XGUIBase();
	virtual ~XGUIBase();
	void addGUIComponent(XGUIComponentBase* pUIComp);
	void removeGUIComponent(XGUIComponentBase* pUIComp);
	inline size_t getID() const {
		return ull_id_;
	}
	inline void setID(const size_t& ull_id) {
		ull_id_ = ull_id;
	}

public:
	XTransform			transform_;
protected:
	XGUIBase			*pParent_;
private:
	size_t				ull_id_;
	size_t				ull_next_component_id_;
};

#endif

