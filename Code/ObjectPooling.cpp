#include "ObjectPooling.h"
#include "XEngine.h"
#include "PhysicsWorld.h"

ObjectPooling::ObjectPooling(PhysicsWorld* pPhys_world)
	:pPhys_world_(pPhys_world)
{
	pObject_map_with_name_ = new std::unordered_map<std::wstring, std::vector<std::shared_ptr<XObject>>>();
	ull_all_GUI_count_ = 0;
}

ObjectPooling::~ObjectPooling()
{
	object_destroy_vec_.clear();
	for (auto& temp : *pObject_map_with_name_) temp.second.clear();
	XDELETE_PTR(pObject_map_with_name_);
}

void ObjectPooling::showObject()
{
	for (size_t i = 0; i < objects_kv_.count(); ++i)
	{
		for (size_t j = 0; j < objects_kv_[i]->child_map_.count(); ++j) {
			objects_kv_[i]->child_map_[j]->show();
		}
		objects_kv_[i]->show();
	}
}

void ObjectPooling::actorRun()
{
	for (size_t i = 0; i < objects_kv_.count(); ++i)
	{
		for (size_t j = 0; j < objects_kv_[i]->child_map_.count(); ++j) {
			objects_kv_[i]->child_map_[j]->run();
		}
		objects_kv_[i]->run();
	}
}

void ObjectPooling::showGUI()
{
	for (size_t i = 0; i < gui_kv_.count(); ++i)
	{
		gui_kv_[i]->showCanvas();
	}
}

void ObjectPooling::runGUI()
{
	for (size_t i = 0; i < gui_kv_.count(); ++i)
	{
		gui_kv_[i]->runCanvas();
	}
}

void ObjectPooling::postProcessing()
{
}

void ObjectPooling::addObject(std::shared_ptr<XObject> pNewActor)
{
	if (pNewActor->getID() != 0)return;
	//int n = objects_kv_.count();
	//pNewActor->setID((size_t)pNewActor.get());
	objects_kv_.pushBack(pNewActor.get(), pNewActor);
	if (pObject_map_with_name_->find(pNewActor->name_) == pObject_map_with_name_->end()) {
		pObject_map_with_name_->insert(std::pair<std::wstring, std::vector<std::shared_ptr<XObject>>>(pNewActor->name_, { pNewActor }));
	}
	else {
		pObject_map_with_name_->at(pNewActor->name_).push_back(pNewActor);
	}
}

void ObjectPooling::addGUIElement(std::shared_ptr<XGUIBase> pNewUI)
{
	if (pNewUI->getID() == 0)pNewUI->setID(++ull_all_GUI_count_);
	gui_kv_.pushBack(pNewUI->getID(), pNewUI);
}

void ObjectPooling::destroyObject()
{
	for (auto& temp : object_destroy_vec_)
	{
		//std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		temp.reset();
	}
	object_destroy_vec_.clear();
	for (auto& temp : gui_destroy_vec_)
	{
		//std::lock_guard<std::mutex> lk_fixed_run(mutex_fixed_run_);
		temp.reset();
	}
	gui_destroy_vec_.clear();
}

void ObjectPooling::removeObject(std::shared_ptr<XObject> pRemove_obj)
{
	//size_t id = pRemove_obj->getID();
	std::wstring name = pRemove_obj->name_;
	XObject* ptr = pRemove_obj.get();
	if (objects_kv_.find(ptr) == false) return;
	object_destroy_vec_.push_back(objects_kv_.atKey(ptr));
	objects_kv_.erase(ptr);

	if (pObject_map_with_name_->find(name) == pObject_map_with_name_->end())return;
	for (auto it = pObject_map_with_name_->at(name).begin(); it != pObject_map_with_name_->at(name).end();)
	{
		if (it->get() == ptr) it = pObject_map_with_name_->at(name).erase(it);
		else it++;
	}
	//if (pObject_map_with_name_->at(name).size() == 0) pObject_map_with_name_->erase(name);
}

void ObjectPooling::removeGUIElement(const size_t& id)
{
	gui_destroy_vec_.push_back(gui_kv_.atKey(id));
	gui_kv_.erase(id);
}

