#include "GameSettings.h"
#include "XTime.h"

GameSettings *GameSettings::pGameSettings_obj_ = nullptr;
long long GameSettings::thread_sleep_time_ = 16;

void GameSettings::setGameMaxFPS(const float& FPS)
{
	XTime::getTimeObj()->setMaxFPS(FPS);
}
