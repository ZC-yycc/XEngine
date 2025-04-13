#ifndef XENGINE_H
#define XENGINE_H

#include "DebugLog.h"
#include "XThreadPool.h"
#include "SceneManager.h"
#include "XWorld.h"
#include "XObject.h"
#include "XDrawLine.h"



class XObject;
class XActor;
class XGUIBase;

#ifndef XENGINEMACRO
#define XENGINEMACRO

#define XDELETE_PTR(ptr) do{if(ptr){delete ptr;ptr = nullptr;}}while(0)

#define XLocalInvoke(...) lInvoke(this,__VA_ARGS__)
#define XGlobalInvoke(...) gInvoke(__VA_ARGS__)

#define XThis shared_from_this()

#endif //XENGINEMACRO

std::shared_ptr<XObject> findObjectWithName(const std::wstring & name);
std::vector<std::shared_ptr<XObject>> findObjectsWithName(const std::wstring & name);



class XEngine 
{
public:
	static XEngine* getInstance() {
		if (pEngine_ == nullptr) pEngine_ = new XEngine();
		return pEngine_;
	}
	static bool getGameState() {
		return gameState;
	}
	static void exitGame() {
		gameState = false;
	}

	static void drawCircle(const Vector2& center, float radius, int segments);
	static void drawLine(const Vector2& begin, const Vector2& end);
	static void drawBox(const Vector2& center, const Vector2& w_h);
	static void drawCircle(const Vector2& center, int radius, int segments = 36);
private:
	static bool							gameState;
	XDrawLine							line_;
	static XEngine						*pEngine_;
};

void destroy(std::shared_ptr<XObject> destroy_obj);

//
//template<class T>
//void destroyGUI(T gui_element)
//{
//	//if (gui_element == nullptr) return;
//	//XCurrentWorld->removeGUI(gui_element->getID());
//	//gui_element = nullptr;
//}
//
//void addNewGUI(std::shared_ptr<XGUIBase> pNewGUI);

template<class T>
std::shared_ptr<T> newObject(const std::wstring& name) {
	std::shared_ptr<T> obj = std::make_shared<T>(name);
	XCurrentWorld->addObject(obj);
	return obj;
}

template<class T>
std::shared_ptr<T> newObject(const std::wstring& name, const Vector2& location) {
	std::shared_ptr<T> obj = std::make_shared<T>(name);
	obj->transform_.location_ = location;
	XCurrentWorld->addObject(obj);
	return obj;
}

template<class T>
std::shared_ptr<T> newObject(const std::wstring& name, const Vector2& location, const Vector2& scale) {
	std::shared_ptr<T> obj = std::make_shared<T>(name);
	obj->transform_.location_ = location;
	obj->transform_.scale_ = scale;
	XCurrentWorld->addObject(obj);
	return obj;
}

template<class T>
std::shared_ptr<T> newObject(const std::wstring& name, const Vector2& location, const float& rotation, const Vector2& scale) {
	std::shared_ptr<T> obj = std::make_shared<T>(name);
	obj->transform_.location_ = location;
	obj->transform_.rotation_ = rotation;
	obj->transform_.scale_ = scale;
	XCurrentWorld->addObject(obj);
	return obj;
}


template<class F,class T, class ...Args>
void lInvoke(T *obj,F &&f, const long long &&delay = 0, Args &&...args) {
	auto f_t = std::bind(f, obj, args...);
	XThreadPool::getThreadPoolObj()->enqueue(f_t, delay);
}

template<class F, class ...Args>
void gInvoke(F&& f, const long long&& delay = 0, Args &&...args) {
	XThreadPool::getThreadPoolObj()->enqueue([=]() {f(args...); }, delay);
}
#endif //XENGINE_H

