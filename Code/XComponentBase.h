#ifndef XCOMPONENTBASE_H
#define XCOMPONENTBASE_H
/*
		�������
����һЩ�������ԣ�����
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
	//�ݹ��ȡ�汲�任����
	void getAllParentTransMat4(XObject* pParent, glm::mat4& all_mat4)const;
	void getAllParentTRMat4(XObject* pParent, glm::mat4 &all_mat4)const;
};

#endif

