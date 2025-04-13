#ifndef XBACKGROUND_H
#define XBACKGROUND_H
#include "XActor.h"

class XStaticMeshComponent;

class XBackground : public XActor
{
public:
	XBackground(const std::wstring &name);
	~XBackground();

	XStaticMeshComponent		*pBackground_;
};

#endif