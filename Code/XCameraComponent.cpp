#include "XCameraComponent.h"
#include "XEngine.h"
#include "GameSettings.h"
#include "CameraManager.h"

XCameraComponent::XCameraComponent(XObject* pBody)
	:XComponentBase(pBody)
{
	transform_.location_ = Vector2(0.0f, 0.0f);
	orthom_mat4_ = glm::ortho(
		-XGameViewportSize().x_ / 2.0f, XGameViewportSize().x_ / 2.0f,
		-XGameViewportSize().y_ / 2.0f, XGameViewportSize().y_ / 2.0f, 100.0f, -100.0f);

	world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);


	CameraManager::getManager()->addCamera(this);
}

XCameraComponent::XCameraComponent(const XTransform &trans, XObject* pBody)
	:XComponentBase(pBody)
{
	transform_.location_ = trans.location_;
	orthom_mat4_ = glm::ortho(
		-XGameViewportSize().x_ / 2.0f, XGameViewportSize().x_ / 2.0f,
		-XGameViewportSize().y_ / 2.0f, XGameViewportSize().y_ / 2.0f, 100.0f, -100.0f);

	world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

	CameraManager::getManager()->addCamera(this);
}

XCameraComponent::XCameraComponent(const Vector2& location, XObject* pBody)
	:XComponentBase(pBody)
{
	transform_.location_ = location;
	orthom_mat4_ = glm::ortho(
		-XGameViewportSize().x_ / 2.0f, XGameViewportSize().x_ / 2.0f,
		-XGameViewportSize().y_ / 2.0f, XGameViewportSize().y_ / 2.0f, 100.0f, -100.0f);
	world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

	CameraManager::getManager()->addCamera(this);
}

XCameraComponent::~XCameraComponent()
{
	CameraManager::getManager()->removeCamera(this->ull_component_id_);
}
void XCameraComponent::OnViewportResize(const Vector2& xy_size, const Vector2& fb_size)
{
	orthom_mat4_ = glm::ortho(xy_size.x_/2, xy_size.x_ / 2.0f, xy_size.y_ / 2, xy_size.y_ / 2.0f, fb_size.x_, fb_size.y_);
}