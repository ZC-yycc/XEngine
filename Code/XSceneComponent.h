#ifndef XSCENECOMPONENT_H
#define XSCENECOMPONENT_H

#include "XComponentBase.h"
#include "XObject.h"

class XSceneComponent : public XComponentBase
{
public:
	XSceneComponent(XObject* pBody);
	virtual ~XSceneComponent();


};

#endif
