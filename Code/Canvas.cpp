#include "Canvas.h"
#include "XImage.h"
#include "Transform.h"
#include "XEngine.h"
#include "XButton.h"
#include "Material.h"
#include "GameSettings.h"
#include "XBlur.h"
#include "XSlideBar.h"
#include "Input.h"

Canvas::Canvas()
{
	//pBlur_ = new XGussianBlurImage(this, "Resource/car.png");
	//pButton_ = new XButton(this);
	//pButton_->pTransform_anchors_->Location_ = Vector2(0, 200);
	//pButton_->pTransform_anchors_->Scale_ = Vector2(5, 3);
	//pButton_->XOnClick(&Canvas::onclick);
	//pButton_->XOnMouseHang(&Canvas::onMouseHang);
	//pButton_->XOnMouseEnter(&Canvas::onMouseEnter);
	//pButton_->XOnMouseOut(&Canvas::onMouseOut);

	//pBlur_->pTransform_center_->Location_ = Vector2(0, 0);
	//pBlur_->pTransform_center_->Scale_ = Vector2(80,45);
	transform_.z_Index_ = 2.0f;

	pBlur_ = new XBlur(this);
	pSlide_ = new XSlideBar(this, Vector2(20, 0.5));
	pSlide_->transform_anchors_.location_ = Vector2(-500, 300);
}

void Canvas::run()
{
	if (Input::getKey(KeyCode::J)) {
		pBlur_->transform_center_.location_.x_ -= 5.0f;
	}
	if (Input::getKey(KeyCode::L)) {
		pBlur_->transform_center_.location_.x_ += 5.0f;
	}
	if (Input::getKey(KeyCode::I)) {
		pBlur_->transform_center_.location_.y_ += 5.0f;
	}
	if (Input::getKey(KeyCode::K)) {
		pBlur_->transform_center_.location_.y_ -= 5.0f;
	}
	//if (Input::getKeyDown(KeyCode::N)) {
	//	pBlur_->enable(!pBlur_->getState());
	//}
	//pImage_->pTransform_->Scale_ = Vector2::lerp(pImage_->pTransform_->Scale_, Vector2(10, 1),0.1f);
	//pTransform_->Scale_ = Vector2::lerp(pTransform_->Scale_, Vector2(2, 0), 0.1f);
	//pImage_->pTransform_anchors_->Scale_ = Vector2::lerp(pImage_->pTransform_anchors_->Scale_, Vector2(10, 1), 0.1f);
}

void Canvas::onclick()
{
	//XENGINE_LOG("On Click");
}

void Canvas::onMouseHang()
{
	//XENGINE_LOG("Hang");
}

void Canvas::onMouseEnter()
{
	//XENGINE_LOG("On Mouse Enter");
}

void Canvas::onMouseOut()
{
	//XENGINE_LOG("On Mouse Out");
}

