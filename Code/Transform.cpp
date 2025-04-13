#include "Transform.h"
#include "XObject.h"

XTransform::XTransform()
{
	location_ = Vector2(0, 0);
	rotation_ = 0.0f;
	scale_ = Vector2(1.0f, 1.0f);
	z_Index_ = 0;
	physics_mat4_ = glm::mat4(1.0f);
}

XTransform::XTransform(const Vector2 &location, const float &rotation, const Vector2 &scaled)
{
	location_ = location;
	rotation_ = rotation;
	scale_ = scaled;
	z_Index_ = 0;
	physics_mat4_ = glm::mat4(1.0f);
}

XTransform::XTransform(const XTransform& input)
{
	location_ = input.location_;
	rotation_ = input.rotation_;
	scale_ = input.scale_;
	z_Index_ = input.z_Index_;
	physics_mat4_ = glm::mat4(1.0f);
}

XTransform::~XTransform()
{
}
