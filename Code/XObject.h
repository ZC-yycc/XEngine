#ifndef XOBJECT_H
#define XOBJECT_H
/*
		游戏对象父类
继承XBehaviorBase接口，定义游戏对象基本数据，父对象指针，子对象列表
*/

#include "InterfaceLib.h"
#include "XComponentBase.h"
#include <string>

namespace XEngineObjectType {
	enum ObjectTypeEnum{
		COMPONENT,
		XOBJECT,
		XACTOR
	};
}

class XObject : public XBehaviorRun, public std::enable_shared_from_this<XObject>
{
	friend XComponentBase;
public:
	XObject(const std::wstring &name);
	virtual ~XObject();
	virtual void show()override;

	void setParent(std::shared_ptr<XObject> pParent);
	void setChild(std::shared_ptr<XObject> pChild);
	void removeChild(std::shared_ptr<XObject> pChild);
	inline size_t getID() const {
		return ull_Id_;
	}
	inline void setID(const size_t &id) {
		this->ull_Id_ = id;
	}
	inline XEngineObjectType::ObjectTypeEnum getObjType()const {
		return obj_type_;
	}
	inline void setObjType(XEngineObjectType::ObjectTypeEnum type) {
		this->obj_type_ = type;
	}
	inline std::shared_ptr<XObject> getParent() const {
		return pParent_;
	}

protected:
	size_t													ull_Id_;
	XEngineObjectType::ObjectTypeEnum						obj_type_;
	std::shared_ptr<XObject>								pParent_;

public:
	std::wstring											name_;
	std::string												sTag_;
	XTransform												transform_;

	XKeyVector<size_t, XComponentBase*>						comp_map_;
	XKeyVector<size_t, std::shared_ptr<XObject>>			child_map_;
};

#endif

