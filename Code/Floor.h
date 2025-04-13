#pragma once
#include "XActor.h"

class XStaticMeshComponent;
class XBoxColliderComponent;

class Floor : public XActor
{
public:
	Floor(const std::wstring& name);
	~Floor();
	virtual void begin()override;


	XBoxColliderComponent* pBox_collision_;
	XStaticMeshComponent* pMesh_;
};

