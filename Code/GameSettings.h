#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include "Transform.h"

#define XGameViewportSize() GameSettings::getGameSettingsObj()->getViewportSize()
#define XGameWindowSize() GameSettings::getGameSettingsObj()->getWindowSize()
#define XGameThreadSleepTime GameSettings::thread_sleep_time_

class GameSettings
{
private:
	GameSettings() {
		window_size_ = Vector2(600, 900);
		//window_size_ = Vector2(1280, 720);
		viewport_size_ = window_size_;
	}
	GameSettings(const GameSettings&) = delete;
	GameSettings operator=(const GameSettings&) = delete;
	static GameSettings* pGameSettings_obj_;
	Vector2 window_size_;
	Vector2 viewport_size_;

public:
	static long long thread_sleep_time_;

public:
	static void setGameMaxFPS(const float &FPS);
	inline void setViewportSize(const int &x, const int &y) {
		viewport_size_ = Vector2((float)x, (float)y);
	}
	inline Vector2 getWindowSize() const {
		return window_size_;
	}
	inline Vector2 getViewportSize() const {
		return viewport_size_;
	}
	static GameSettings* getGameSettingsObj() {
		if (pGameSettings_obj_ == nullptr) pGameSettings_obj_ = new GameSettings();
		return pGameSettings_obj_;
	}
};

#endif
