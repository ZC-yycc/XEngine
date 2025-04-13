#ifndef XWORLD_H
#define XWORLD_H

#include <string>
#include <vector>
#include "XObject.h"

#define XRayTest(...) SceneManager::getCurrentWorld()->rayTest(__VA_ARGS__)

class ObjectPooling;
class PhysicsWorld;
class XGUIBase;
class XRayHitInfo;

class XWorld
{
public:
	XWorld();
	~XWorld();
public:
	ObjectPooling			*pObject_pooling_;
	PhysicsWorld			*pPhys_world_;

public:
	void deleteObject();
	void show();
	void postProcessing();
	void runThread();
	void updatePhysWorld();
	void collisionDetection();
	size_t getObjectCount()const;
	void rayTest(const Vector2& begin, const Vector2& end, XRayHitInfo &rayhit);

public:
	void addObject(std::shared_ptr<XObject> new_object);
	void addGUI(std::shared_ptr<XGUIBase> new_GUI);
	void removeGUI(const size_t &id);
	std::shared_ptr<XObject> findObjectWithName(const std::wstring& name);
	std::vector<std::shared_ptr<XObject>> findObjectsWithName(const std::wstring& name);
	void removeObject(std::shared_ptr<XObject> remove_object);
	void removeObjects(const std::wstring &name);
};
#endif
