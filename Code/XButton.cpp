#include "XButton.h"
#include "XImage.h"
#include "XGUIBase.h"
#include "Input.h"
#include "XEngine.h"

XButton::XButton(XGUIBase* pCanvas, const std::string& click_file, const std::string& hang_file, const std::string& gene_file)
	:XGUIComponentBase(pCanvas)
{
	pImage_hang_ = new XImage(nullptr,hang_file);
	pImage_general_ = new XImage(nullptr,gene_file);
	pImage_click_ = new XImage(nullptr,click_file);

	bMouse_last_state_ = false;

	fHalf_length_ = transform_center_.scale_.x_;
	fHalf_width_ = transform_center_.scale_.y_;

	fLeft_border_ = transform_center_.location_.x_ - fHalf_length_;
	fRight_border_ = transform_center_.location_.x_ + fHalf_length_;
	fUp_border_ = transform_center_.location_.y_ + fHalf_width_;
	fDown_border_ = transform_center_.location_.y_ - fHalf_width_;
}

XButton::~XButton()
{
	XDELETE_PTR(pImage_hang_);
	XDELETE_PTR(pImage_general_);
	XDELETE_PTR(pImage_click_);
}

void XButton::show()
{
	Vector2 temp = Input::getMousePosOrigin();
	if (temp.x_ > fLeft_border_ && temp.x_ < fRight_border_ &&
		temp.y_ > fDown_border_ && temp.y_ < fUp_border_) {
		if (Input::getKey(KeyCode::LButton)) {
			pImage_click_->show();
			return;
		}
		else {
			pImage_hang_->show();
			return;
		}
	}
	pImage_general_->show();
}

void XButton::run()
{
	Vector2 temp = Input::getMousePosOrigin();
	transUpdate();
	fHalf_length_ = transform_anchors_.scale_.x_ ;
	fHalf_width_ = transform_anchors_.scale_.y_;

	fLeft_border_ = transform_anchors_.location_.x_ - fHalf_length_;
	fRight_border_ = transform_anchors_.location_.x_ + fHalf_length_;
	fUp_border_ = transform_anchors_.location_.y_ + fHalf_width_;
	fDown_border_ = transform_anchors_.location_.y_ - fHalf_width_;

	if (temp.x_ > fLeft_border_ && temp.x_ < fRight_border_ &&
		temp.y_ > fDown_border_ && temp.y_ < fUp_border_) {
		if (bMouse_last_state_ == false && onBtn_enter_ != nullptr) {
			onBtn_enter_();
			bMouse_last_state_ = true;
		}
		if (Input::getKeyDown(KeyCode::LButton) && onclick_func_ != nullptr) onclick_func_();
		if (hang_func_ != nullptr) hang_func_();
	}
	else {
		if (bMouse_last_state_ == true && onBtn_out_ != nullptr) {
			onBtn_out_();
			bMouse_last_state_ = false;
		}
	}
}

void XButton::transUpdate()
{
	pImage_hang_->transform_anchors_ = transform_anchors_;
	pImage_general_->transform_anchors_ = transform_anchors_;
	pImage_click_->transform_anchors_ = transform_anchors_;
	pImage_hang_->transform_center_ = transform_center_;
	pImage_general_->transform_center_ = transform_center_;
	pImage_click_->transform_center_ = transform_center_;
}
