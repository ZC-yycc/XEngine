#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <map>
#include <string>
#include "XArray.h"

#ifndef XSCENEMACRO
#define XSCENEMACRO

#define XCurrentWorld SceneManager::getCurrentWorld()
#define XGetWrold(x)  SceneManager::getSceneManagerObj()->getWorld(x)

#endif //XSCENEMACRO

class XWorld;
class PhysicsWorld;

class SceneManager
{
private:
	XKeyVector<std::wstring, XWorld*>		world_kv_;

	static std::wstring						sCurrent_world_;
	static SceneManager						*pScene_manager_obj_;
private:
	SceneManager();
public:
	~SceneManager();
	inline static SceneManager* getSceneManagerObj() {
		if (pScene_manager_obj_ == nullptr)pScene_manager_obj_ = new SceneManager();
		return pScene_manager_obj_;
	}
	inline XWorld* getWorld(const std::wstring& world_name){
		if (!world_kv_.find(world_name)) return nullptr;
		return world_kv_.atKey(world_name);
	}
	inline XWorld* getWorld(const size_t& index) {
		return world_kv_[index];
	}
	static inline XWorld* getCurrentWorld(){
		if (!pScene_manager_obj_->world_kv_.find(sCurrent_world_)) return nullptr;
		return pScene_manager_obj_->world_kv_.atKey(sCurrent_world_);
	}
	inline size_t getCurrentWorldIndex(){
		return world_kv_.getIndex(sCurrent_world_);
	}
	static inline void setCurrentWorld(const std::wstring& world_name) {
		sCurrent_world_ = world_name;
	}
	static inline void setCurrentWorld(const int& index) {
		sCurrent_world_ = pScene_manager_obj_->world_kv_.getKey(index);
	}
	inline void addWorld(const std::wstring &world_name, XWorld* newWorld) {
		world_kv_.pushBack(world_name, newWorld);
	}
	size_t getCurrentObjectCount();

	void deleteObject();
	void show();
	void postProcessing();
	void runThread();
	void updatePhysWorld();
	void collisionDetection();
};

#endif