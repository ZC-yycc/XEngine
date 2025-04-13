#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

/*
		摄像机管理类
管理摄像机主次关系，获取主摄像机，添加，移除摄像机
*/
#include <unordered_map>
#include <mutex>
#include "XCameraComponent.h"

class CameraManager
{
	friend XCameraComponent;
public:
	CameraManager();
	~CameraManager();
	
	inline bool setMainCamera(const size_t &camera_id) {
		std::unique_lock<std::mutex> lk(mutex_get_camera_);
		if (pCamera_umap_->find(camera_id) == pCamera_umap_->end()) return false;
		pMain_camera_ = pCamera_umap_->at(camera_id);
		return true;
	}

	inline static XCameraComponent* getMainCamera() {
		std::unique_lock<std::mutex> lk(pCamera_manager_obj_->mutex_get_camera_);
		if (pMain_camera_ == nullptr) pMain_camera_ = pCamera_manager_obj_->pCamera_umap_->at(0);
		return pMain_camera_;
	}

	inline XCameraComponent* getCamera(const int &camera_id) {
		std::unique_lock<std::mutex> lk(mutex_get_camera_);
		if (pCamera_umap_->find(camera_id) == pCamera_umap_->end()) return nullptr;
		return pCamera_umap_->at(camera_id);
	}

	inline static CameraManager* getManager() {
		if (pCamera_manager_obj_ == nullptr) pCamera_manager_obj_ = new CameraManager();
		return pCamera_manager_obj_;
	}

private:
	void addCamera(XCameraComponent	*pNew_camera);
	void removeCamera(const size_t&camera_id);

private:
	static XCameraComponent							*pMain_camera_;
	size_t											ull_next_camera_id_;
	std::unordered_map<size_t,XCameraComponent*>	*pCamera_umap_;
	static CameraManager							*pCamera_manager_obj_;
	std::mutex										mutex_get_camera_;
};

#endif
