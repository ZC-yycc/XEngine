#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H
/*
		模拟物理
封装bullet物理引擎，创建基本的物理世界
*/
//#include <btBulletDynamicsCommon.h>
#include <map>
#include <unordered_map>
#include <mutex>
#include "Transform.h"
#include "XEngine.h"
#include "XArray.h"


class XColliderComponent;
// 碰撞检测回调
class CollisionPartInfo : public btCollisionWorld::ContactResultCallback
{
public:
	btScalar addSingleResult(
		btManifoldPoint& point,
		const btCollisionObjectWrapper* pCol_obj_wrap_0,
		int partId_0,
		int index_0,
		const btCollisionObjectWrapper* pCol_obj_wrap_1,
		int partId_1,
		int index_1)
	{
		//XENGINE_LOG(point.getDistance());
		if (point.getDistance() > 0.1f)return 0;
		point_ = Vector2(point.getPositionWorldOnA().x(), point.getPositionWorldOnA().y());
		//XENGINE_LOG("x " << pCol_obj_wrap_0->getWorldTransform().getOrigin().x() <<" y "<< pCol_obj_wrap_0->getWorldTransform().getOrigin().x());
		bIs_overlap_ = true;
		return 0;
	};
public:
	Vector2					point_ = { 0,0 };
	bool					bIs_overlap_ = false;
};

class XRayHitInfo : public btCollisionWorld::RayResultCallback
{
public:
	XRayHitInfo(const Vector2 &begin, const Vector2 &end)
		: ray_from_(btVector3(begin.x_, begin.y_, 0)),ray_to_(btVector3(end.x_, end.y_, 0))
	{}

	float addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)override
	{
		m_collisionObject = rayResult.m_collisionObject;
		m_collisionObjects.push_back(rayResult.m_collisionObject);

		btVector3 hitPointWorld;
		hitPointWorld.setInterpolate3(ray_from_, ray_to_, rayResult.m_hitFraction);
		m_hitPointWorld.push_back(hitPointWorld);
		return m_closestHitFraction;
	}
	btVector3										ray_from_;
	btVector3										ray_to_;

	inline size_t getColliderCount() const {
		return m_collisionObjects.size();
	}

	inline Vector2 getHitPoint(const int& index) {
		return Vector2(m_hitPointWorld[index].x(), m_hitPointWorld[index].y());
	}

	inline XColliderComponent* getCollider(const int& index) {
		return static_cast<XColliderComponent*>(m_collisionObjects[index]->getUserPointer());
	}
private:
	btAlignedObjectArray<btVector3>					m_hitPointWorld;
	btAlignedObjectArray<const btCollisionObject*>	m_collisionObjects;
};

class PhysicsWorld
{

private:
	XKeyVector<size_t, XColliderComponent*>			pCollisionObjects_map_;
	size_t											ull_next_id_;
	Vector2											gravity_;
public:
	PhysicsWorld();
	~PhysicsWorld();

	inline Vector2 getGravity() const {
		return gravity_;
	}
	inline btVector3 getBtGravity() const {
		return btVector3(gravity_.x_, gravity_.y_, 0.0f);
	}
	inline void setGravity(const Vector2 &new_gravity) {
		gravity_ = new_gravity;
		pDynamics_world_->setGravity(btVector3(gravity_.x_, gravity_.y_, 0.0f));
	}
	void updatePhysics(const float &planck_time);
	void collisionDetection();
	void addRigidBody(XColliderComponent* const rigid);
	void removeRigidBody(const size_t &rigid_body_id);
	void add6DofConstraint(btGeneric6DofConstraint *const constraint);
	void rayTest(const Vector2& begin, const Vector2& end, XRayHitInfo &rayhit);
private:
	btDbvtBroadphase						*pBroadphase_AABB_;
	btAxisSweep3							*pBroadphase_DBVT_;
	btDefaultCollisionConfiguration			*pColl_Config_;
	btCollisionDispatcher					*pDispatcher_;
	btSequentialImpulseConstraintSolver		*pSolver_;
	btDiscreteDynamicsWorld					*pDynamics_world_;
};

#endif
