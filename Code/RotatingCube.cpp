#include "RotatingCube.h"
#include "XStaticMeshComponent.h"
#include "XEngine.h"
#include "Input.h"

RotatingCube::RotatingCube(const std::wstring &name)
	:XActor(name)
{
	pMesh_ = new XStaticMeshComponent(Vector2(0, 0), 0.0f, Vector2(10.0f, 10.0f), "Resource/tile.png", this);
	transform_.z_Index_ = 0.1f;
}

RotatingCube::~RotatingCube()
{
	XDELETE_PTR(pMesh_);
}

void RotatingCube::run()
{
	if (Input::getKeyDown(KeyCode::Q)) {
		transform_.z_Index_ += 0.1f;
		XENGINE_LOG(transform_.z_Index_);
	}
}
