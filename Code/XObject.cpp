#include "XObject.h"
#include "DebugLog.h"
#include "XActor.h"
#include "XEngine.h"
#include "PhysicsWorld.h"
#include <functional>

XObject::XObject(const std::wstring &name)
{
	ull_Id_ = 0;
	name_ = name;
	pParent_ = nullptr;
}

XObject::~XObject() 
{
	if (pParent_ != nullptr) {
		pParent_->child_map_.erase(ull_Id_);
	}
	child_map_.clear();
}

void XObject::show()
{
	for (size_t i = 0; i < comp_map_.count(); ++i)
	{
		comp_map_[i]->show();
	}
}

void XObject::setParent(std::shared_ptr<XObject> pParent)
{
	if (pParent == nullptr && pParent_ == nullptr) return;
	else if (pParent != nullptr && pParent_ == nullptr) {
		obj_type_ = XEngineObjectType::COMPONENT;
		pParent_ = pParent;
		if(ull_Id_ != 0)destroy(XThis);
		int id = pParent->child_map_.count();
		ull_Id_ = ++id;
		pParent->child_map_.pushBack(ull_Id_, XThis);
	}
	else if (pParent != nullptr && pParent_ != nullptr) {
		obj_type_ = XEngineObjectType::COMPONENT;
		pParent_ = pParent;
		pParent_->child_map_.erase(ull_Id_);
		int id = pParent->child_map_.count();
		ull_Id_ = ++id;
		pParent->child_map_.pushBack(ull_Id_, XThis);
	}
	else if (pParent == nullptr && pParent_ != nullptr) {
		obj_type_ = XEngineObjectType::XOBJECT;
		XCurrentWorld->addObject(XThis);
		pParent_->child_map_.erase(ull_Id_);
		pParent_ = pParent;
		ull_Id_ = 0;
	}
}

void XObject::setChild(std::shared_ptr<XObject> pChild)
{
	if (pChild == nullptr) {
		XENGINE_LOG("XObject::setChild : pChild is nullptr");
		return;
	}
	pChild->obj_type_ = XEngineObjectType::COMPONENT;
	if (pChild->pParent_ != nullptr) {
		pChild->pParent_->child_map_.erase(ull_Id_);
	}
	int id = child_map_.count();
	pChild->ull_Id_ = ++id;
	child_map_.pushBack(pChild->ull_Id_, pChild);
}

void XObject::removeChild(std::shared_ptr<XObject> pChild)
{
	if (pChild == nullptr) return;
	if (!child_map_.find(pChild->ull_Id_)) return;

	std::shared_ptr<XObject> pChild_temp = child_map_[pChild->ull_Id_];
	pChild_temp->pParent_ = nullptr;
	XCurrentWorld->addObject(std::shared_ptr<XObject>(pChild_temp));
	child_map_.erase(pChild->ull_Id_);
	pChild->obj_type_ = XEngineObjectType::COMPONENT;
}



