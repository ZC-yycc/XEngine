#ifndef XCOLLIDERCOMPONENT_H
#define XCOLLIDERCOMPONENT_H
#include "XComponentBase.h"
#include "ThirdPartyLib/bullet/src/btBulletDynamicsCommon.h"
#include <functional>
#include "PhysicsWorld.h"


/*
			��ײ���������
Collisder+RigidBody�������ģ��������ײ��������
*/

class XWorld;
struct btDefaultMotionState;

#ifndef XONCOLLISIONOVERLAP
#define XONCOLLISIONOVERLAP
#define XOnCollisionBeginOverlap(F) bindBeginOverlapFunc(this, F)
#define XOnCollisionEndOverlap(F) bindEndOverlapFunc(this, F)
#define XOnCollisionOverlap(F) bindOverlapFunc(this, F)
#endif //XONCOLLISIONOVERLAP


class XColliderComponent : public XComponentBase
{
	friend void PhysicsWorld::collisionDetection();
public:

	XColliderComponent(PhysicsWorld* pPhys_world, XObject* body);
	virtual ~XColliderComponent();

	//����������ģ������ݸ��µ���Ⱦ����
	void updateTransform();

	//����ԭʼRigidBody����
	inline btRigidBody* getRigidBody()const {
		return pRigid_body_;
	}

	//����ƽ��Լ��
	inline btGeneric6DofConstraint* getPlaneConstraint()const {
		return pPlane_constraint_;
	}

	inline XObject* getObject()const {
		return pBody_;
	}

//-----��������
#if 1
	//����RigidBody������
	inline void setMass(const float &mass) {
		fMass_ = mass;
		btVector3 localInertia(0, 0, 0);
		pShape_->calculateLocalInertia(fMass_, localInertia);
		pRigid_body_->setMassProps(bDynamic_ ? fMass_ : 0.0f, localInertia);
	}

	//����RigidBody�Ƿ�Ϊ��̬
	inline void setDynamic(const bool &is_dynamic) {
		btVector3 localInertia(0, 0, 0);
		bDynamic_ = is_dynamic;
		pShape_->calculateLocalInertia(fMass_, localInertia);
		pRigid_body_->setMassProps(is_dynamic ? fMass_ : 0.0f, localInertia);
	}

	//�Ƿ�Ϊ������
	inline void isTrigger(const bool& is_trigger) {
		is_trigger ?
			pRigid_body_->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE) : pRigid_body_->setCollisionFlags(nDefaultFlags_);
	}

	//�����
	inline void addForceMoment(const Vector2 &force_vec) {
		if(pRigid_body_ != nullptr)
			pRigid_body_->applyCentralForce(btVector3(force_vec.x_, force_vec.y_, 0.0f));
	}

	//�������
	inline void addTorque(const Vector2& vec) {
		if (pRigid_body_ != nullptr)
			pRigid_body_->applyTorque(btVector3(vec.x_, vec.y_, 0.0f));
	}

	//��������ٶ�
	inline void setLinearVelocity(const Vector2 &velocity) {
		if(pRigid_body_ != nullptr)
			pRigid_body_->setLinearVelocity(btVector3(velocity.x_, velocity.y_, 0));
	}
	
	//����Ħ����
	inline void setFriction(const float &friction) {
		if(pRigid_body_ != nullptr)
			pRigid_body_->setFriction(friction);
	}
	
	//���÷���ϵ��
	inline void setRestitution(const float &rest) {
		if (pRigid_body_ != nullptr)
			pRigid_body_->setRestitution(rest);
	}
	
	//������������
	inline void setLinearDamping(const float& lin_damping) {
		if (pRigid_body_ != nullptr) {
			fLinear_damping_ = lin_damping;
			pRigid_body_->setDamping(fLinear_damping_,fAngular_damping_);
		}
	}

	//���ý�����
	inline void setAngularDamping(const float& ang_damping) {
		if (pRigid_body_ != nullptr) {
			fAngular_damping_ = ang_damping;
			pRigid_body_->setDamping(fLinear_damping_, fAngular_damping_);
		}
	}

	//���ý��ٶ�
	inline void setAngularVelocity(const float &ang_vel) {
		if (pRigid_body_ != nullptr)
			pRigid_body_->setAngularVelocity(btVector3(0, 0, ang_vel));
	}

	//��������
	inline void setGravity(const Vector2& vec) {
		if (pRigid_body_ != nullptr)
			pRigid_body_->setGravity(btVector3(vec.x_, vec.y_, 0.0f));
	}

	//����λ��
	inline void translate(const Vector2& location) {
		if (pRigid_body_ != nullptr)
			pRigid_body_->translate(btVector3(location.x_, location.y_, 0.0f));
	}

	//��������
	inline void enableGravity(const bool& enable) {
		enable ? pRigid_body_->setGravity(pPhys_world_->getBtGravity()) : pRigid_body_->setGravity(btVector3(0,0,0));
	}

	//�����֡,������������������
	inline void clearForcesMoment() {
		if (pRigid_body_ != nullptr)
			pRigid_body_->clearForces();
	}

	//�����֡����
	inline void clearGravityMoment() {
		if (pRigid_body_ != nullptr)
			pRigid_body_->clearGravity();
	}
#endif


//-----��ȡ����
#if 1

	//���ظ�������
	inline float getMass() const {
		return fMass_;
	}
	
	//��ȡRigidBody״̬
	inline bool getDynamicState() const {
		return bDynamic_;
	}

	//��ȡ������
	inline float getAngularDamping() const {
		return fAngular_damping_;
	}

	//��ȡ��������
	inline float getLinearDamping() const {
		return fLinear_damping_;
	}

	//��ȡ����
	inline Vector2 getTotalForce() const {
		return Vector2(pRigid_body_->getTotalForce().x(), pRigid_body_->getTotalForce().y());
	}

	//��ȡ��������
	inline Vector2 getTotalTorque() const {
		return Vector2(pRigid_body_->getTotalTorque().x(), pRigid_body_->getTotalTorque().y());
	}

	//��ȡ���ٶ�
	inline float getAngularVelocity() const {
		return pRigid_body_->getAngularVelocity().z();
	}

#endif

//����
#if 1
public:
	size_t								ull_rigid_body_ID_;
	int									nDefaultFlags_;
	bool								bLast_state_;
	std::unordered_map<size_t, bool>						collision_states_;
	std::function<void(XObject* const, const Vector2&)>		overlap_call_back_;
	std::function<void(XObject* const, const Vector2&)>		begin_overlap_call_back_;
	std::function<void(XObject* const, const Vector2&)>		end_overlap_call_back_;

protected:
	float								fMass_;
	float								fLinear_damping_;
	float								fAngular_damping_;
	bool								bDynamic_;

protected:
	PhysicsWorld						*pPhys_world_;
	btDefaultMotionState				*pMotion_state_;
	btRigidBody							*pRigid_body_;
	btTransform							last_trans_;
	btCollisionShape					*pShape_;
	btGeneric6DofConstraint				*pPlane_constraint_;
#endif

public:
	template<class Temp_Type>
	void bindOverlapFunc( Temp_Type* const Obj_0, void(Temp_Type::* func)(XObject* const obj_1, const Vector2& point)) {
		this->overlap_call_back_ = std::bind(func, Obj_0, std::placeholders::_1, std::placeholders::_2);
	}
	template<class Temp_Type>
	void bindBeginOverlapFunc(Temp_Type* const Obj_0, void(Temp_Type::* func)(XObject* const obj_1, const Vector2& point)) {
		this->begin_overlap_call_back_ = std::bind(func, Obj_0, std::placeholders::_1, std::placeholders::_2);
	}
	template<class Temp_Type>
	void bindEndOverlapFunc( Temp_Type* const Obj_0, void(Temp_Type::* func)(XObject* const obj_1, const Vector2& point)) {
		this->end_overlap_call_back_ = std::bind(func, Obj_0, std::placeholders::_1, std::placeholders::_2);
	}

protected:
	void rigidInit();
};

//������ײ��
class XBoxColliderComponent : public XColliderComponent
{
public:
	XBoxColliderComponent(const Vector2& location, const float& rotation, const Vector2& w_h,
		XWorld* pPhys_world, XObject* body);
	XBoxColliderComponent(const Vector2& w_h, XWorld* pPhys_world, XObject* body);
	virtual ~XBoxColliderComponent();

	inline void resize(const Vector2 &size) {
		pPhys_world_->removeRigidBody(ull_rigid_body_ID_);
		XDELETE_PTR(pShape_);
		scale_ = size;
		pShape_ = new btBoxShape(btVector3(size.x_, size.y_, 10.0f));
		pRigid_body_->setCollisionShape(pShape_);
		pPhys_world_->addRigidBody(this);
	}
public:
	Vector2							scale_;
};

//������ײ��
class XSphereColliderComponent : public XColliderComponent
{
public:
	XSphereColliderComponent(const Vector2 &location,const float &rotation,const float& radius,
		XWorld* pWorld, XObject* body);
	XSphereColliderComponent(const float &radius, XWorld* pWorld, XObject* body);
	virtual ~XSphereColliderComponent();

	inline void resize(const float &radius) {
		pPhys_world_->removeRigidBody(ull_rigid_body_ID_);
		XDELETE_PTR(pShape_);
		fRadius_ = radius;
		pShape_ = new btSphereShape(fRadius_);
		pRigid_body_->setCollisionShape(pShape_);
		pPhys_world_->addRigidBody(this);
	}
public:
	float							fRadius_;
};

//��������ײ��
class XCapsuleColliderComponent : public XColliderComponent
{
public:
	XCapsuleColliderComponent(const Vector2& location, const float& rotation, const float& radius, const float& height,
		XWorld* pWorld, XObject* body);
	XCapsuleColliderComponent(const float &radius, const float &height, XWorld* pWorld, XObject* body);
	virtual ~XCapsuleColliderComponent();

	inline void resize(const float& fRadius, const float& fHeight) {
		pPhys_world_->removeRigidBody(ull_rigid_body_ID_);
		XDELETE_PTR(pShape_);
		fRadius_ = fRadius;
		fHeight_ = fHeight;
		pShape_ = new btCapsuleShape(fRadius,fHeight);
		pRigid_body_->setCollisionShape(pShape_);
		pPhys_world_->addRigidBody(this);
	}

private:
	float							fRadius_;
	float							fHeight_;
};

//ƽ��
class XPlaneColliderComponent : public XColliderComponent
{
public:
	XPlaneColliderComponent(const Vector2 &vec2, XWorld* pWorld, XObject* body);
	virtual ~XPlaneColliderComponent();

public:
	Vector2							normal_;
};

#endif