#include "MoveCube.h"
#include "XEngine.h"
#include "XStaticMeshComponent.h"
#include "Input.h"
#include "CameraManager.h"
#include "XCameraComponent.h"
#include "XColliderComponent.h"
#include "SceneManager.h"
#include "XWorld.h"
#include "Material.h"
#include "Texture.h"
#include "Bullet.h"
#include "XTime.h"

MoveCube::MoveCube(const std::wstring& name)
	:XActor(name)
{
}

void MoveCube::begin()
{
	transform_.location_ = Vector2(0.0f, 0.0f);
	transform_.scale_ = Vector2(1.0f, 1.0f);
	transform_.z_Index_ = 1.0f;

	pMesh_ = new XStaticMeshComponent(Vector2(0, 0), 0.0f, Vector2(30.0f, 30.0f), "Resource/emojis.png", this);
	pSphere_collision_ = new XSphereColliderComponent(Vector2(0, 0), 0.0f, 30.0f, XGetWrold(L"beginWorld"), this);

	pSphere_collision_->setAngularDamping(0.5f);
	pSphere_collision_->XOnCollisionBeginOverlap(&MoveCube::beginOverlap);
	pSphere_collision_->XOnCollisionEndOverlap(&MoveCube::endOverlap);
	pCamera_ = new XCameraComponent(transform_, this);
	speed_ = 10.0f;

	CameraManager::getManager()->setMainCamera(pCamera_->ull_component_id_);
}

MoveCube::~MoveCube()
{
	XDELETE_PTR(pMesh_);
	XDELETE_PTR(pSphere_collision_);
}

void MoveCube::run()
{
	//XEngine::drawBox(transform_.location_, transform_.scale_ *2);
	//XEngine::drawCircle(transform_.location_, 10.0f);
	//物体移动
	transform_.location_.x_ += Input::getAxis(XAxis::Horizontal) * speed_;
	transform_.location_.y_ += Input::getAxis(XAxis::Vertical) * speed_;

	/* Camera 跟随 */
	pCamera_->transform_.location_ = Vector2::lerp(pCamera_->transform_.location_, transform_.location_, 0.1f);
	

	/* 射线检测 */
	//XRayHitInfo hit_info(Vector2(-10, 0), Vector2(10, 0));
	//XRayTest(Vector2(-10, 0), Vector2(10, 0), hit_info);
	//if (hit_info.hasHit()) {
	//	//XENGINE_LOG("ray hit!");
	//	//XENGINE_LOG(hit_info.getColliderCount());
	//	//XENGINE_LOG(hit_info.getHitPoint(0).x_, hit_info.getHitPoint(0).y_);
	//	//XENGINE_LOG(hit_info.getCollider(0)->ull_component_id_);
	//}

	// 曲线测试 需要pSphere_collision_->setDynamic(false);
	/* lerp 曲线测试 */
	//transform_.location_ = Vector2::lerp(transform_.location_, Vector2(300, 300), 0.1f);

	/* backEaseOut 曲线测试 */
	//if (Input::getKey(KeyCode::R)) {
	//	time_ += 0.05f;
	//	transform_.location_.x_ = Vector2::backEaseOut(time_, 2.0f, 0.0f, 300.0f);
	//	XENGINE_LOG(transform_.location_.x_);
	//}

	/* backEaseIn 曲线测试 */
	//if (Input::getKey(KeyCode::T)) {
	//	time_ += 0.05f;
	//	transform_.location_.x_ = Vector2::backEaseIn(time_, 2.0f, 0.0f, 300.0f);
	//	XENGINE_LOG(transform_.location_.x_);
	//}
}

void MoveCube::beginOverlap(XObject* const obj, const Vector2& point)
{
	//XENGINE_LOG("MoveCube " << ull_Id_ << " Begin Overlap with " << obj->getID() << " point :"<< point.x_<<" "<<point.y_);
	//destroy(XThis);
}

void MoveCube::endOverlap(XObject* const obj, const Vector2& point)
{
	//XENGINE_LOG("MoveCube " << ull_Id_ << " End Overlap with " << obj->getID() << " point :" << point.x_ << " " << point.y_);
}

void MoveCube::overlap(std::shared_ptr<XObject> obj, const Vector2& point)
{
	//XENGINE_LOG("MoveCube " << ull_Id_ << " Overlap with " << obj->getID() << " point :" << point.x_ << " " << point.y_);
}

void MoveCube::invokeTest(int a, char c)
{
	//XENGINE_LOG("invokeTest:: a:" << a << "  c:" << c);
	//destroy(XThis);
}

void MoveCube::slideCallback(const float& value)
{
	//XENGINE_LOG("slideCallback  " << value);
}

void MoveCube::slideMaxCallback()
{
	//XENGINE_LOG("slide_Max_Callback");
}

void MoveCube::slideMinCallback()
{
	//XENGINE_LOG("slide_Min_Callback");
}


