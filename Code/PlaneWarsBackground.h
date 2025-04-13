#pragma once
#include "XActor.h"

class XStaticMeshComponent;

class PlaneWarsBackground : public XActor
{
public:
	PlaneWarsBackground(const std::wstring& name);
	~PlaneWarsBackground();
	void run()override;

	XStaticMeshComponent* pBackground_;
	float						speed_;
};

