#include "PlaneWarsBackground.h"
#include "XStaticMeshComponent.h"
#include "XEngine.h"
#include "Material.h"
#include "XTime.h"

PlaneWarsBackground::PlaneWarsBackground(const std::wstring& name)
	:XActor(name)
{
	pBackground_ = new XStaticMeshComponent(Vector2(0, 0), 0.0f, Vector2(300, 450), "Resource/back.png", this);
	transform_.z_Index_ = 0.0f;
	speed_ = 0.5f;
}

PlaneWarsBackground::~PlaneWarsBackground()
{
	XDELETE_PTR(pBackground_);
}

void PlaneWarsBackground::run()
{
	pBackground_->pMaterial_->uv_offset_.y_ += speed_ * XTime::getDeltaTime();
}
