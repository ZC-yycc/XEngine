#include "XComponentBase.h"
#include "GameSettings.h"
#include "XObject.h"
#include "XEngine.h"

XComponentBase::XComponentBase(XObject* pBody)
	:pBody_(pBody)
{
	if (pBody_ == nullptr) return;
	ull_component_id_ = pBody_->comp_map_.count();	
	pBody_->comp_map_.pushBack(ull_component_id_, this);
}

XComponentBase::~XComponentBase()
{
}

glm::mat4 XComponentBase::getTransMat4()const
{
	glm::mat4 Body_mat4 = transform_.getWorldTransMat4();
	if (pBody_ != nullptr) getAllParentTransMat4(pBody_, Body_mat4);
	return Body_mat4;
}

glm::mat4 XComponentBase::getTRMat4() const
{
	glm::mat4 Body_mat4 = transform_.getTRMat4();
	if (pBody_ != nullptr) getAllParentTRMat4(pBody_, Body_mat4);
	return Body_mat4;
}

void XComponentBase::getAllParentTransMat4(XObject* pParent, glm::mat4 &all_mat4)const
{
	if (pParent == nullptr) return;
	all_mat4 = pParent->transform_.getWorldTransMat4() * all_mat4;
	getAllParentTransMat4(pParent->pParent_.get(), all_mat4);
}

void XComponentBase::getAllParentTRMat4(XObject* pParent, glm::mat4& all_mat4) const
{
	if (pParent == nullptr) return;
	all_mat4 = pParent->transform_.getTRMat4() * all_mat4;
	getAllParentTRMat4(pParent->pParent_.get(), all_mat4);
}



