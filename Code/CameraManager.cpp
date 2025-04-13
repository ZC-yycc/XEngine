#include "CameraManager.h"
#include "XEngine.h"


CameraManager* CameraManager::pCamera_manager_obj_ = new CameraManager();
XCameraComponent *CameraManager::pMain_camera_ = new XCameraComponent(Vector2(0.0f, 0.0f));

CameraManager::CameraManager()
{
	ull_next_camera_id_ = 0;
	pCamera_umap_ = new std::unordered_map<size_t, XCameraComponent*>();
	pMain_camera_ = nullptr;
}

CameraManager::~CameraManager()
{
	for (auto& temp : *pCamera_umap_) {
		XDELETE_PTR(temp.second);
	}
	XDELETE_PTR(pCamera_umap_);
}

void CameraManager::addCamera(XCameraComponent *pNew_camera)
{
	pNew_camera->ull_component_id_ = ull_next_camera_id_++;
	std::unique_lock<std::mutex> lk(mutex_get_camera_);
	pCamera_umap_->insert(std::pair<size_t, XCameraComponent*>(pNew_camera->ull_component_id_, pNew_camera));
}

void CameraManager::removeCamera(const size_t &camera_id)
{
	if (camera_id == 0)return;
	std::unique_lock<std::mutex> lk(mutex_get_camera_);
	std::unordered_map<size_t, XCameraComponent*>::iterator it = pCamera_umap_->find(camera_id);
	pCamera_umap_->erase(it);
}
