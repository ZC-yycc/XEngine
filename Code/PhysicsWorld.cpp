#include "PhysicsWorld.h"
#include "XColliderComponent.h"
#include "XTime.h"


PhysicsWorld::PhysicsWorld()
	:ull_next_id_(1), gravity_(0.0f, -10.0f)
{
	pBroadphase_AABB_ = new btDbvtBroadphase();
	pBroadphase_DBVT_ = new btAxisSweep3(btVector3(-1000,-1000,-10), btVector3(1000, 1000, 10), 1024);
	pColl_Config_ = new btDefaultCollisionConfiguration();
	pDispatcher_ = new btCollisionDispatcher(pColl_Config_);
	pSolver_ = new btSequentialImpulseConstraintSolver();
	pDynamics_world_ = new btDiscreteDynamicsWorld(pDispatcher_, pBroadphase_DBVT_, pSolver_, pColl_Config_);

	pDynamics_world_->setGravity(btVector3(gravity_.x_, gravity_.y_, 0));
}

PhysicsWorld::~PhysicsWorld()
{
	XDELETE_PTR(pDynamics_world_);
	XDELETE_PTR(pBroadphase_AABB_);
	XDELETE_PTR(pBroadphase_DBVT_);
	XDELETE_PTR(pColl_Config_);
	XDELETE_PTR(pDispatcher_);
	XDELETE_PTR(pSolver_);
}

void PhysicsWorld::updatePhysics(const float& planck_time)
{
	pDynamics_world_->stepSimulation(planck_time, 20);
	
	for (size_t i = 0; i < pCollisionObjects_map_.count(); ++i)
		pCollisionObjects_map_[i]->updateTransform();
}

void PhysicsWorld::collisionDetection()
{
	XColliderComponent* pCol_0 = nullptr;
	XColliderComponent* pCol_1 = nullptr;
	size_t key = 0;
	bool last_state_t = false;
	for (size_t i = 0; i < pCollisionObjects_map_.count(); ++i)
	{
		for (size_t j = 0; j < pCollisionObjects_map_.count(); ++j)
		{
			if (i == j)continue;
			pCol_0 = pCollisionObjects_map_[i];
			pCol_1 = pCollisionObjects_map_[j];
			key = pCollisionObjects_map_.getKey(i);
			if (pCol_1->collision_states_.find(key) == pCol_1->collision_states_.end()) {
				pCol_1->collision_states_.insert(std::pair<size_t, bool>(pCol_0->ull_rigid_body_ID_, false));
			}
			CollisionPartInfo col_info;
			pDynamics_world_->contactPairTest(pCol_0->getRigidBody(), pCol_1->getRigidBody(), col_info);
			last_state_t = pCol_1->collision_states_[key];
			if (last_state_t == col_info.bIs_overlap_ && last_state_t) {
				if (pCol_0->overlap_call_back_ != nullptr)
					pCol_0->overlap_call_back_(pCol_1->pBody_, col_info.point_);
			}
			else if(last_state_t > col_info.bIs_overlap_){
				if (pCol_0->end_overlap_call_back_ != nullptr)
					pCol_0->end_overlap_call_back_(pCol_1->pBody_, col_info.point_);
			}
			else if(last_state_t < col_info.bIs_overlap_){
				if (pCol_0->begin_overlap_call_back_ != nullptr)
					pCol_0->begin_overlap_call_back_(pCol_1->pBody_, col_info.point_);
			}
			pCol_1->collision_states_[key] = col_info.bIs_overlap_;
		}
	}
}

void PhysicsWorld::addRigidBody(XColliderComponent* const rigid)
{
	pDynamics_world_->addRigidBody(rigid->getRigidBody());
	if(rigid->ull_rigid_body_ID_ == 0) rigid->ull_rigid_body_ID_ = ull_next_id_++;
	pCollisionObjects_map_.pushBack(rigid->ull_rigid_body_ID_, rigid);
}

void PhysicsWorld::removeRigidBody(const size_t& rigid_body_id)
{
	if (!pCollisionObjects_map_.find(rigid_body_id)) return;
	XColliderComponent* rigid_temp = pCollisionObjects_map_.atKey(rigid_body_id);
	pDynamics_world_->removeConstraint(rigid_temp->getPlaneConstraint());
	pDynamics_world_->removeRigidBody(rigid_temp->getRigidBody());
	pCollisionObjects_map_.erase(rigid_body_id);
}

void PhysicsWorld::add6DofConstraint(btGeneric6DofConstraint* const constraint)
{
	pDynamics_world_->addConstraint(constraint);
}

void PhysicsWorld::rayTest(const Vector2& begin, const Vector2& end, XRayHitInfo &rayhit)
{
	pDynamics_world_->rayTest(btVector3(begin.x_, begin.y_, 0), btVector3(end.x_, end.y_, 0), rayhit);
}
