#ifndef OBJECTPOOLING_H
#define OBJECTPOOLING_H
/*
		对象资源管理类
存储,增加，删除对象
*/
#include "XArray.h"
#include "XActor.h"
#include "XGUIBase.h"
#include <memory>

class PhysicsWorld;

class ObjectPooling
{
public:
	ObjectPooling(PhysicsWorld *pPhys_world);
	~ObjectPooling();

	void showObject();
	void actorRun();

	void showGUI();
	void runGUI();

	void postProcessing();

	//添加对象到容器中
	void addObject(std::shared_ptr<XObject> pNewActor);

	void addGUIElement(std::shared_ptr<XGUIBase> pNewUI);

	//移除对象
	void removeObject(std::shared_ptr<XObject> pRemove_obj);

	void removeGUIElement(const size_t& id);

	//要销毁的对象
	void destroyObject();


	//获取对象个数
	inline size_t getCount()
	{
		//std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		return objects_kv_.count();
	}

	inline std::vector<std::shared_ptr<XObject>> findObjectsWithName(const std::wstring& name) const {
		if (pObject_map_with_name_->find(name) == pObject_map_with_name_->end())return {};
		return pObject_map_with_name_->at(name);
	}

	inline std::shared_ptr<XObject> findObjectWithName(const std::wstring& name) const {
		if (pObject_map_with_name_->find(name) == pObject_map_with_name_->end())return nullptr;
		return pObject_map_with_name_->at(name).at(0);
	}

private:

	XKeyVector<XObject*, std::shared_ptr<XObject>>					objects_kv_;

	std::unordered_map
		<std::wstring, std::vector<std::shared_ptr<XObject>>>		*pObject_map_with_name_;
	PhysicsWorld													*pPhys_world_;

private:
	std::vector<std::shared_ptr<XGUIBase>>							gui_destroy_vec_;
	std::vector<std::shared_ptr<XObject>>							object_destroy_vec_;

private:
	size_t															ull_all_GUI_count_;
	XKeyVector<size_t, std::shared_ptr<XGUIBase>>					gui_kv_;

};

#endif
