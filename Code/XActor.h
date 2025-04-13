#ifndef XACTOR_H
#define XACTOR_H

#include "XObject.h"


class XActor : public XObject
{
public:

	XActor(const std::wstring &name);
	virtual ~XActor();
};


#endif // !XACTOR_H


