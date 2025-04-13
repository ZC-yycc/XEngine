#include "Player.h"
#include "XStaticMeshComponent.h"
#include "XColliderComponent.h"
#include "SceneManager.h"
#include "XEngine.h"
#include "Bullet.h"
#include "Input.h"
#include "XTime.h"

Player::Player(const std::wstring &name)
	:Plane(name)
{
}

void Player::begin()
{
	transform_.scale_ = Vector2(1, 1);
	pBox_ = new XBoxColliderComponent(Vector2(20.0f, 30.0f), XGetWrold(L"beginWorld"), this);
	pPlane_img_ = new XStaticMeshComponent(Vector2(0, 0), 0, Vector2(20.0f, 30.0f), "Resource/me1.png", this);
	pBox_->setGravity(Vector2(0, 0));
	pBox_->isTrigger(true);
	pBox_->XOnCollisionBeginOverlap(&Player::beginOverlap);
	fSpeed_ = 400.0f;
	transform_.z_Index_ = 2.0f;
}


void Player::run()
{
	float&& axis_h_temp = Input::getAxis(XAxis::Horizontal);
	float&& axis_v_temp = Input::getAxis(XAxis::Vertical);
	transform_.location_.x_ += axis_h_temp * fSpeed_ * XTime::getDeltaTime();
	transform_.location_.y_ += axis_v_temp * fSpeed_ * XTime::getDeltaTime();

	if (Input::getKeyDown(KeyCode::J)) {
		newObject<Bullet>(L"Bullet", transform_.location_ + Vector2(0, 50.0f));
	}

	if (Input::getKey(KeyCode::L)) fSpeed_ = 600.0f;
	else fSpeed_ = 400.0f;

}

Player::~Player()
{
	XDELETE_PTR(pPlane_img_);
	XDELETE_PTR(pBox_);
}

void Player::beginOverlap(XObject* const pOther, const Vector2& point)
{
	if (pOther->name_ == L"Enemy")destroy(XThis);
}
