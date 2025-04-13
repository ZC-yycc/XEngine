#include "XColliderComponent.h"
#include "Transform.h"
#include "XObject.h"
#include "XMath.h"
#include "XWorld.h"
#include "SceneManager.h"
#include <mutex>

XBoxColliderComponent::XBoxColliderComponent(const Vector2& location, const float& rotation, const Vector2& w_h, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_, body), scale_(w_h)
{
	transform_.location_ = location;
	transform_.rotation_ = rotation;
	pShape_ = new btBoxShape(btVector3(scale_.x_,scale_.y_, 10));
	pShape_->setMargin(0.0f);
	rigidInit();
}

XBoxColliderComponent::XBoxColliderComponent(const Vector2& w_h, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_,body), scale_(w_h)
{
	pShape_ = new btBoxShape(btVector3(scale_.x_,scale_.y_, 10));
	pShape_->setMargin(0.0f);
	rigidInit();
}


XSphereColliderComponent::XSphereColliderComponent(const Vector2& location, const float& rotation, const float& radius, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_, body), fRadius_(radius)
{
	transform_.location_ = location;
	transform_.rotation_ = rotation;
	pShape_ = new btSphereShape(fRadius_);
	pShape_->setMargin(0.0f);
	rigidInit();
}

XSphereColliderComponent::XSphereColliderComponent(const float& radius, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_,body), fRadius_(radius)
{
	pShape_ = new btSphereShape(fRadius_);
	pShape_->setMargin(0.0f);
	rigidInit();
}


XCapsuleColliderComponent::XCapsuleColliderComponent(const Vector2& location, const float& rotation, const float& radius, const float& height, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_, body), fHeight_(height), fRadius_(radius)
{
	transform_.location_ = location;
	transform_.rotation_ = rotation;
	pShape_ = new btCapsuleShape(fRadius_,fHeight_);
	rigidInit();
}

XCapsuleColliderComponent::XCapsuleColliderComponent(const float& radius, const float& height, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_,body), fHeight_(height), fRadius_(radius)
{
	pShape_ = new btCapsuleShape(fRadius_,fHeight_);
	rigidInit();
}

XPlaneColliderComponent::XPlaneColliderComponent(const Vector2& vec2, XWorld* pWorld, XObject* body)
	:XColliderComponent(pWorld->pPhys_world_, body)
{
	pShape_ = new btStaticPlaneShape(btVector3(vec2.x_, vec2.y_, 0), 1);
	rigidInit();
}

XColliderComponent::XColliderComponent(PhysicsWorld* pPhys_world, XObject* body)
	:XComponentBase(body), pPhys_world_(pPhys_world)
{
	fMass_ = 1;
	bDynamic_ = true;
	ull_rigid_body_ID_ = 0;
	btTransform trans;
	trans.setIdentity();
	trans.setFromOpenGLMatrix(glm::value_ptr(getTRMat4()));
	last_trans_ = trans;
	pMotion_state_ = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), last_trans_.getOrigin()));
}

XBoxColliderComponent::~XBoxColliderComponent()
{
}

XSphereColliderComponent::~XSphereColliderComponent()
{
}

XCapsuleColliderComponent::~XCapsuleColliderComponent()
{
}

XPlaneColliderComponent::~XPlaneColliderComponent()
{
}


XColliderComponent::~XColliderComponent()
{
	pPhys_world_->removeRigidBody(ull_rigid_body_ID_);
	XDELETE_PTR(pMotion_state_);
	XDELETE_PTR(pRigid_body_);
	XDELETE_PTR(pShape_);
	XDELETE_PTR(pPlane_constraint_);
	overlap_call_back_ = nullptr;
	begin_overlap_call_back_ = nullptr;
	end_overlap_call_back_ = nullptr;
}


//将物理世界模拟的数据更新到渲染世界
void XColliderComponent::updateTransform()
{
	if (pRigid_body_ == nullptr) return;
	if (pBody_ == nullptr) return;
	//初始化临时变量
	btTransform trans_temp_get;
	trans_temp_get.setIdentity();
	trans_temp_get = pRigid_body_->getWorldTransform();

	pBody_->transform_.setTransFromBtTrans(trans_temp_get.getOrigin() - last_trans_.getOrigin(),
		XTransform::getEulerAngle(trans_temp_get) - XTransform::getEulerAngle(last_trans_));

	trans_temp_get.setIdentity();
	trans_temp_get.setFromOpenGLMatrix(glm::value_ptr(getTRMat4()));

	pRigid_body_->setWorldTransform(trans_temp_get);

	pRigid_body_->activate(true);
	last_trans_ = trans_temp_get;
}

//初始化RigidBody
void XColliderComponent::rigidInit()
{
	btVector3 localInteria(0, 0, 0);
	pShape_->calculateLocalInertia(fMass_, localInteria);
	btRigidBody::btRigidBodyConstructionInfo rigid_const_info(fMass_, pMotion_state_, pShape_, localInteria);
	pRigid_body_ = new btRigidBody(rigid_const_info);
	nDefaultFlags_ = pRigid_body_->getCollisionFlags();
	fLinear_damping_ = pRigid_body_->getLinearDamping();
	fAngular_damping_ = pRigid_body_->getAngularDamping();
	
	//创建约束，约束在XY平面内，限制X，Y轴的旋转
	pPlane_constraint_ = new btGeneric6DofConstraint(*pRigid_body_, btTransform::getIdentity(), true);
	pPlane_constraint_->setLinearLowerLimit(btVector3(1, 1, 0));
	pPlane_constraint_->setLinearUpperLimit(btVector3(-1, -1, 0));
	pPlane_constraint_->setAngularLowerLimit(btVector3(0, 0, 90.0f));
	pPlane_constraint_->setAngularUpperLimit(btVector3(0, 0, 0));

	//向世界添加约束，添加刚体
	pPhys_world_->add6DofConstraint(pPlane_constraint_);
	pPhys_world_->addRigidBody(this);

	//设置用户指针，用于碰撞检测的函数回调
	pRigid_body_->setUserPointer(this);
}