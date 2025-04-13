#include "Enemy.h"
#include "GameSettings.h"
#include "XEngine.h"
#include "XStaticMeshComponent.h"
#include "XColliderComponent.h"
#include "SceneManager.h"
#include "XTime.h"
#include "Bullet.h"

Enemy::Enemy(const std::wstring& name)
	:Plane(name)
{
}

Enemy::~Enemy()
{
	XDELETE_PTR(pPlane_img_);
	XDELETE_PTR(pBox_);
}

void Enemy::begin()
{
	transform_.scale_ = Vector2(1.0f, 1.0f);
	transform_.location_ = Vector2(XMath::randInt(-200.0f, 200.0f), XMath::randInt(XGameViewportSize().y_ / 2.0f, (XGameViewportSize().y_ / 2.0f) - 200.0f));
	transform_.z_Index_ = 1.0f;
	fSpeed_ = 100.0f;
	fProgress_ = 0.0f;
	fHP_ = 20.0f;
	pPlane_img_ = new XStaticMeshComponent(Vector2(0, 0), 0, Vector2(20.0f, 30.0f), "Resource/enemy2_hit.png", this);
	pBox_ = new XBoxColliderComponent(Vector2(20.0f, 30.0f), XGetWrold(L"beginWorld"), this);
	pBox_->setGravity(Vector2(0, 0));
	pBox_->isTrigger(true);
	pBox_->XOnCollisionBeginOverlap(&Enemy::beginOverlap);
}

void Enemy::run()
{
	transform_.location_.y_ -= fSpeed_ * XTime::getDeltaTime();
	fProgress_ -= XTime::getDeltaTime();
	if (transform_.location_.y_ < (-XGameViewportSize().y_ / 2.0f)) {
		transform_.location_ = Vector2(XMath::randInt(-200.0f, 200.0f), XMath::randInt(XGameViewportSize().y_ / 2.0f, (XGameViewportSize().y_ / 2.0f) - 400.0f));
		fHP_ = 20.0f;
	}
	if (fProgress_ <= 0.0f) {
		std::shared_ptr<Bullet> bullet = newObject<Bullet>(L"Bullet", transform_.location_ - Vector2(0, 40.0f));
		bullet->nVec_ = -1;
		fProgress_ = XMath::randFloat(1,3);
	}
}

void Enemy::beginOverlap(XObject* const pOther, const Vector2& point)
{
	if (pOther->name_ == L"Player")destroy(XThis);
}
