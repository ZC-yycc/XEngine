#ifndef ROTATINGCUBE_H
#define ROTATINGCUBE_H

#include "XActor.h"

class XStaticMeshComponent;

class RotatingCube : public XActor
{
public:
	RotatingCube(const std::wstring& name);
	~RotatingCube();

	XStaticMeshComponent* pMesh_;

	void run()override;
};

#endif