#ifndef OCUBE_H
#define OCUBE_H

#include "XObject.h"

class XStaticMeshComponent;
class XBoxColliderComponent;


class Cube : public XObject
{
public:
	Cube(const std::wstring &name);
	~Cube();
	virtual void begin()override;

	void overlap(XObject* obj, const Vector2& point);
	void beginOverlap(XObject* obj, const Vector2& point);
	void endOverlap(XObject* obj, const Vector2& point);

	XBoxColliderComponent			*pBox_collision_;
	XStaticMeshComponent			*pMesh_;
};

#endif
