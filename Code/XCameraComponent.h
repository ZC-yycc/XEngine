#ifndef XCAMERACOMPONENT_H
#define XCAMERACOMPONENT_H

#include "XComponentBase.h"
#include "XMath.h"

class XCameraComponent : public XComponentBase
{
public:
	XCameraComponent(XObject* pBody = nullptr);
	XCameraComponent(const XTransform &trans, XObject* pBody = nullptr);
	XCameraComponent(const Vector2& location, XObject* pBody = nullptr);
	~XCameraComponent();

	inline glm::mat4 getViewMat()const {
		glm::mat4 mat_temp = glm::lookAt(glm::vec3(transform_.location_.x_, transform_.location_.y_, 0.0f), 
			glm::vec3(transform_.location_.x_, transform_.location_.y_, -1.0f),
			world_up_);
		return mat_temp;
	}
	inline glm::mat4 getOrthomMat() const {
		return orthom_mat4_;
	}

	void OnViewportResize(const Vector2& xy_size, const Vector2& fb_size);
private:
	glm::vec3				world_up_;
	glm::mat4				orthom_mat4_;

};

#endif 

