#pragma once
#include "Plane.h"

class XStaticMeshComponent;
class XBoxColliderComponent;

class Player : public Plane
{
public:
	Player(const std::wstring& name);
	~Player();
	void run()override;
	void begin()override;
	void beginOverlap(XObject* const pOther, const Vector2& point);

private:
	XStaticMeshComponent        *pPlane_img_;
	XBoxColliderComponent		*pBox_;
};

