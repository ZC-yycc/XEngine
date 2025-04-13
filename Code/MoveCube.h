#ifndef MOVECUBE_H
#define MOVECUBE_H
#include "XActor.h"
class XStaticMeshComponent;
class XCameraComponent;
class Cube;
class RotatingCube;
class XSphereColliderComponent;
class XBoxColliderComponent;

class MoveCube : public XActor
{
public:
	MoveCube(const std::wstring &name);
	~MoveCube();

	virtual void begin()override;
	void run() override;

	void beginOverlap(XObject* const obj, const Vector2& point);
	void endOverlap(XObject* const obj, const Vector2& point);
	void overlap(std::shared_ptr<XObject>obj, const Vector2& point);
	void invokeTest(int a, char c);
	void slideCallback(const float& value);
	void slideMaxCallback();
	void slideMinCallback();
public:
	XStaticMeshComponent		*pMesh_;

	XCameraComponent			*pCamera_;
	XSphereColliderComponent	*pSphere_collision_;

	float						time_;
	float						speed_;


};
#endif
