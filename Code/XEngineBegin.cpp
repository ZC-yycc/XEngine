#include "XEngineBegin.h"
#include "XWorld.h"
#include "XEngine.h"
#include "XColliderComponent.h"
#include "SceneManager.h"
#include "MoveCube.h"
#include "Cube.h"
#include "Floor.h"
#include "Canvas.h"
#include "XSlideBar.h"
#include "XBackground.h"
#include "PlaneWarsBackground.h"
#include "XTime.h"
#include "Enemy.h"
#include "Player.h"

WorldConstructor::WorldConstructor()
{
	XWorld *pBegin_world = new XWorld();
	SceneManager::getSceneManagerObj()->addWorld(L"beginWorld", pBegin_world);
	SceneManager::getSceneManagerObj()->setCurrentWorld(L"beginWorld");


	//std::shared_ptr<XBackground> pBackground_ = newObject<XBackground>(L"小球背景");
	//std::shared_ptr<MoveCube> pMove_cube = newObject<MoveCube>(L"小球");
	//std::shared_ptr<Floor> pFloor = newObject<Floor>(L"地板", Vector2(0.0f, -300.0f));
	//std::shared_ptr<Cube> pCube = newObject<Cube>(L"cube", Vector2(0.0f, -100.0f));


	//pFloor->pBox_collision_->setDynamic(false);
	//pMove_cube->pSphere_collision_->setDynamic(true);
	//pCube->pBox_collision_->setDynamic(true);


	std::shared_ptr<PlaneWarsBackground> pBackground_ = newObject<PlaneWarsBackground>(L"飞机大战背景");
	std::shared_ptr<Enemy> pEnemy_0 = newObject<Enemy>(L"Enemy");
	std::shared_ptr<Enemy> pEnemy_1 = newObject<Enemy>(L"Enemy");
	std::shared_ptr<Enemy> pEnemy_2 = newObject<Enemy>(L"Enemy");
	std::shared_ptr<Enemy> pEnemy_3 = newObject<Enemy>(L"Enemy");

	std::shared_ptr<Player> pPlayer = newObject<Player>(L"Player");

}
