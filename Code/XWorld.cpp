#include "XWorld.h"
#include "ObjectPooling.h"
#include "PhysicsWorld.h"
#include "XEngine.h"


XWorld::XWorld()
{
	pPhys_world_ = new PhysicsWorld();
	pObject_pooling_ = new ObjectPooling(pPhys_world_);
}

XWorld::~XWorld()
{
	XDELETE_PTR(pObject_pooling_);
	XDELETE_PTR(pPhys_world_);
}

void XWorld::deleteObject()
{
	pObject_pooling_->destroyObject();
}

void XWorld::addObject(std::shared_ptr<XObject> new_object)
{
	//XENGINE_LOG(new_object.use_count());
	pObject_pooling_->addObject(new_object);
	new_object->begin();
	//XENGINE_LOG(new_object.use_count());
}

void XWorld::addGUI(std::shared_ptr<XGUIBase> new_GUI)
{
	pObject_pooling_->addGUIElement(new_GUI);
}

void XWorld::removeGUI(const size_t& id)
{
	pObject_pooling_->removeGUIElement(id);
}

std::shared_ptr<XObject> XWorld::findObjectWithName(const std::wstring& name)
{
	return pObject_pooling_->findObjectWithName(name);
}

std::vector<std::shared_ptr<XObject>> XWorld::findObjectsWithName(const std::wstring& name)
{
	return pObject_pooling_->findObjectsWithName(name);
}

void XWorld::show()
{
	pObject_pooling_->showGUI();
	pObject_pooling_->showObject();
}

void XWorld::postProcessing()
{
	pObject_pooling_->showObject();
}

void XWorld::runThread()
{
	pObject_pooling_->actorRun();
	pObject_pooling_->runGUI();
}

void XWorld::updatePhysWorld()
{
	pPhys_world_->updatePhysics(1.0f);
}

void XWorld::collisionDetection()
{
	pPhys_world_->collisionDetection();
}

size_t XWorld::getObjectCount() const
{
	return pObject_pooling_->getCount();
}

void XWorld::rayTest(const Vector2& begin, const Vector2& end, XRayHitInfo &rayhit)
{
	pPhys_world_->rayTest(begin, end, rayhit);
}

void XWorld::removeObject(std::shared_ptr<XObject> remove_object)
{
	pObject_pooling_->removeObject(remove_object);
}

