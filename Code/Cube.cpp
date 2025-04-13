#include "Cube.h"
#include "XStaticMeshComponent.h"
#include "XColliderComponent.h"
#include "XEngine.h"
#include "SceneManager.h"

Cube::Cube(const std::wstring& name)
	:XObject(name)
{

}

void Cube::beginOverlap(XObject* obj, const Vector2& point)
{
	//XENGINE_LOG("Cube "<< ull_Id_ <<" Begin Overlap with " << obj->getID() << " point :" << point.x_ << " " << point.y_);
}

void Cube::endOverlap(XObject* obj, const Vector2& point)
{
	//XENGINE_LOG("Cube " << ull_Id_ << " End Overlap with " << obj->getID() << " point :" << point.x_ << " " << point.y_);
}

void Cube::overlap(XObject* obj, const Vector2& point)
{
	//XENGINE_LOG("Cube " << ull_Id_ << " Overlap with " << obj->getID() << " point :" << point.x_ << " " << point.y_);
	//XENGINE_LOG("x :"<<point.x_ << "y :"<<point.y_);
}

Cube::~Cube()
{
	XDELETE_PTR(pMesh_);
	XDELETE_PTR(pBox_collision_);
}

void Cube::begin()
{
	transform_.scale_ = Vector2(1.0f, 1.0f);
	transform_.z_Index_ = 2.0f;
	pMesh_ = new XStaticMeshComponent(Vector2(0, 0), 0.0f, Vector2(30.0f, 30.0f), "Resource/Cube_m.png", this);
	pBox_collision_ = new XBoxColliderComponent(Vector2(30.0f, 30.0f), XGetWrold(L"beginWorld"), this);

	//pBox_collision_->bindOverlapFunc<Cube>(&Cube::overlap, this);
	pBox_collision_->XOnCollisionBeginOverlap(&Cube::beginOverlap);
	pBox_collision_->XOnCollisionEndOverlap(&Cube::endOverlap);
}

