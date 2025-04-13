#include "Floor.h"
#include "XEngine.h"
#include "XStaticMeshComponent.h"
#include "XColliderComponent.h"


Floor::Floor(const std::wstring& name)
	:XActor(name)
{
}

Floor::~Floor()
{
	XDELETE_PTR(pBox_collision_);
	XDELETE_PTR(pMesh_);
}

void Floor::begin()
{
	transform_.scale_ = Vector2(1.0f, 1.0f);
	transform_.z_Index_ = 2.0f;
	pMesh_ = new XStaticMeshComponent(Vector2(0, 0), 0.0f, Vector2(300.0f, 30.0f), "Resource/Cube_m.png", this);
	pBox_collision_ = new XBoxColliderComponent(Vector2(300.0f, 30.0f), XGetWrold(L"beginWorld"), this);
}

