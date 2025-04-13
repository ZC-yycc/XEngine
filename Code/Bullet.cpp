#include "Bullet.h"
#include "XStaticMeshComponent.h"
#include "XColliderComponent.h"
#include "SceneManager.h"
#include "XEngine.h"
#include "Player.h"
#include "GameSettings.h"
#include "Enemy.h"
#include "XTime.h"

Bullet::Bullet(const std::wstring& name)
	:XActor(name), damage_(11.0f)
{
	pMesh_ = new XStaticMeshComponent(Vector2(0, 0), 0, Vector2(2, 4), "Resource/red.png", this);
	transform_.z_Index_ = 1.0f;
	pBox_col_ = new XBoxColliderComponent(Vector2(2, 4), XGetWrold(L"beginWorld"), this);
	pBox_col_->isTrigger(true);
	pBox_col_->enableGravity(false);
	pBox_col_->XOnCollisionBeginOverlap(&Bullet::beginOverlap);
	nVec_ = 1;
}

Bullet::~Bullet()
{
	XDELETE_PTR(pMesh_);
	XDELETE_PTR(pBox_col_);
}

void Bullet::run()
{
	transform_.location_.y_ += (1000.0f * nVec_ *XTime::getDeltaTime());
	if (transform_.location_.y_ >= XGameViewportSize().y_ / 2.0f)destroy(XThis);
	if (transform_.location_.y_ <= -XGameViewportSize().y_ / 2.0f)destroy(XThis);
}

void Bullet::beginOverlap(XObject* const pOther,const Vector2 &point)
{
	XENGINE_LOG("overlap");
	if (pOther->name_ == L"Player") {
		Player* pPlayer = dynamic_cast<Player*>(pOther);
		if (pPlayer != nullptr) {
			pPlayer->withholdBlood(damage_);
			destroy(XThis);
		}
	}
	else if(pOther->name_ == L"Enemy"){
		Enemy* pEnemy = dynamic_cast<Enemy*>(pOther);
		if (pEnemy != nullptr) {
			pEnemy->withholdBlood(damage_);
			destroy(XThis);
		}
	}
	else{
		destroy(XThis);
	}
}

