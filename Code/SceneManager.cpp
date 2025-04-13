#include "SceneManager.h"
#include "XWorld.h"
#include "XEngine.h"

SceneManager *SceneManager::pScene_manager_obj_ = new SceneManager();
std::wstring SceneManager::sCurrent_world_ = L"defaultWorld";

SceneManager::SceneManager() 
{
	XWorld* pDefault_world = new XWorld();
	addWorld(L"defaultWorld", pDefault_world);
}

SceneManager::~SceneManager()
{
	for (size_t i = 0;i < world_kv_.count(); i++)
	{
		XDELETE_PTR(world_kv_[i]);
	}
}

size_t SceneManager::getCurrentObjectCount()
{
	return getCurrentWorld()->getObjectCount();
}

void SceneManager::deleteObject()
{
	world_kv_.atKey(sCurrent_world_)->deleteObject();
}

void SceneManager::show()
{
	world_kv_.atKey(sCurrent_world_)->show();
}

void SceneManager::postProcessing()
{
	world_kv_.atKey(sCurrent_world_)->postProcessing();
}

void SceneManager::runThread()
{
	world_kv_.atKey(sCurrent_world_)->runThread();
}

void SceneManager::updatePhysWorld()
{
	world_kv_.atKey(sCurrent_world_)->updatePhysWorld();
}

void SceneManager::collisionDetection()
{
	world_kv_.atKey(sCurrent_world_)->collisionDetection();
}
