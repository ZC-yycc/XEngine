#ifndef XCOMPONENTBASE_H
#define XCOMPONENTBASE_H
/*
		组件基类
声明一些公用属性，声明
*/
#include "Transform.h"
#include "InterfaceLib.h"

class XObject;

class XComponentBase : public XBehaviorRun
{
public:
	XComponentBase(XObject* pBody);
	virtual ~XComponentBase();

public:
	size_t						ull_component_id_;
	XTransform					transform_;
protected:
	XObject						*pBody_;
protected:
	glm::mat4 getTransMat4()const;
	glm::mat4 getTRMat4()const;

private:
	//递归获取祖辈变换矩阵
	void getAllParentTransMat4(XObject* pParent, glm::mat4& all_mat4)const;
	void getAllParentTRMat4(XObject* pParent, glm::mat4 &all_mat4)const;
};

#endif

