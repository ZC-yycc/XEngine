#pragma once
#include "Plane.h"

class XStaticMeshComponent;
class XBoxColliderComponent;

class Enemy : public Plane
{
public:
	Enemy(const std::wstring &name);
	~Enemy();
	void begin()override;
	void run()override;
	void beginOverlap(XObject* const pOther, const Vector2& point);

private:
	XStaticMeshComponent		*pPlane_img_;
	XBoxColliderComponent		*pBox_;

	float						fProgress_;
};

