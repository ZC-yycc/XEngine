#include "Plane.h"
#include "XEngine.h"
#include "GameSettings.h"

Plane::Plane( const std::wstring& name)
	:XActor(name), fHP_(100.0f), fDamage_(11.1f), fSpeed_(5.0f)
{
}

Plane::~Plane()
{
}

void Plane::withholdBlood(const float& val)
{
	fHP_ -= val;
	if (fHP_ >= 0) return;
	if (name_ == L"Player") destroy(XThis);
	transform_.location_ = Vector2(XMath::randInt(-200.0f, 200.0f), XMath::randInt(XGameViewportSize().y_ / 2.0f, (XGameViewportSize().y_ / 2.0f) - 200.0f));
	fHP_ = 20.0f;
}
