#include "XBackground.h"
#include "XStaticMeshComponent.h"
#include "XEngine.h"
#include "Material.h"
#include "XTime.h"

XBackground::XBackground(const std::wstring& name)
	:XActor(name)
{
	pBackground_ = new XStaticMeshComponent(Vector2(0, 0), 0.0f, Vector2(1280, 720),"Resource/car1.png", this);
	transform_.z_Index_ = 0.0f;
}

XBackground::~XBackground()
{
	XDELETE_PTR(pBackground_);
}
