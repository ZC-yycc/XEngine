#include "XGUIComponentBase.h"
#include "XGUIBase.h"
#include "XEngine.h"
#include "GameSettings.h"



XGUIComponentBase::XGUIComponentBase(XGUIBase* pCanvas)
	:pCanvas_(pCanvas), trans_mat4_(1.0f)
{
	ull_id_ = 0;
	bEnable_ = true;
	if (pCanvas_ != nullptr) pCanvas_->addGUIComponent(this);
}

XGUIComponentBase::~XGUIComponentBase()
{
	if (pCanvas_ != nullptr) pCanvas_->removeGUIComponent(this);
}

glm::mat4 XGUIComponentBase::getTransMat4()
{
	glm::mat4 temp_mat = trans_mat4_ * transform_anchors_.getWorldTransMat4() * transform_center_.getWorldTransMat4();
	for (XGUIBase* temp = pCanvas_; temp != nullptr; temp = temp->pParent_) {
		temp_mat = temp->transform_.getWorldTransMat4() * temp_mat;
	}
	return temp_mat;
}