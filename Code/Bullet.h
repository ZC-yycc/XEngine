#ifndef BULLET_H
#define BULLET_H

#include "XActor.h"

class XStaticMeshComponent;
class XBoxColliderComponent;


class Bullet : public XActor
{
public:
	Bullet(const std::wstring& name);
	~Bullet();
	void run()override;
	void beginOverlap(XObject* const pOther, const Vector2& point);

public:
	float							damage_;
	int								nVec_;
	XStaticMeshComponent			*pMesh_;
	XBoxColliderComponent			*pBox_col_;
};

#endif