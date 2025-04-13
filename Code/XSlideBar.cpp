#include "XSlideBar.h"
#include "XImage.h"

XSlideBar::XSlideBar(XGUIBase* pCanvas, const Vector2& scale, const std::string& sBackground_file,
	const std::string& sStrip_file, const float& value)
	:XGUIComponentBase(pCanvas), fLast_value_(value),fValue_(value),scale_(scale)
{
	pStrip_ = new XImage(nullptr, sStrip_file);
	pBackground_ = new XImage(nullptr, sBackground_file);
	pBackground_->transform_center_.location_ = Vector2(scale_.x_, 0);
	pBackground_->transform_center_.scale_ = Vector2(scale_.x_, scale_.y_);

	//pStrip_->transform_anchors_.z_Index_ = 0.0f;
	//pStrip_->transform_center_.z_Index_ = 10.0f;

	pStrip_->transform_center_.location_ = Vector2(10, 0);
	pStrip_->transform_anchors_.scale_ = Vector2(0, scale_.y_);
	fMin_ = 0.0f; fMax_ = 1.0f;
	value_change_callback_ = nullptr;
	value_min_callback_ = nullptr;
	value_max_callback_ = nullptr;
}

XSlideBar::~XSlideBar()
{
	XDELETE_PTR(pBackground_);
	XDELETE_PTR(pStrip_);
}

void XSlideBar::show()
{
	pStrip_->trans_mat4_ = getTransMat4();
	pBackground_->trans_mat4_ = getTransMat4();
	pStrip_->show();
	pBackground_->show();
}

void XSlideBar::run()
{
	if (fValue_ > fMax_)fValue_ = fMax_;
	if (fValue_ < fMin_)fValue_ = fMin_;
	pStrip_->transform_anchors_.scale_ = Vector2::lerp(pStrip_->transform_anchors_.scale_,
		Vector2((fValue_/fMax_) * scale_.x_, scale_.y_), 0.1f);
	if (fValue_ != fLast_value_) {
		if(value_change_callback_ != nullptr)value_change_callback_(fValue_);
		fLast_value_ = fValue_;
	}
	if (fValue_ == fMax_ && value_max_callback_ != nullptr) value_max_callback_();
	if (fValue_ == fMin_ && value_min_callback_ != nullptr) value_min_callback_();
}

