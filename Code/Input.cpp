#include "Input.h"
#include "XEngine.h"
#include "GameSettings.h"

Input* Input::pInput_obj_ = new Input();
std::mutex   mutex_getObj;

Input::Input(){
	addKey(KeyCode::A);
	addKey(KeyCode::D);
	addKey(KeyCode::J);
	addKey(KeyCode::S);
	addKey(KeyCode::W);
	addKey(KeyCode::L);
	addKey(KeyCode::K);
	addKey(KeyCode::I);
	addKey(KeyCode::Shift);
	addKey(KeyCode::Space);
	addKey(KeyCode::Enter);
}

Input::~Input()
{
	pInput_obj_ = nullptr;
}

Input* Input::getInputObj()
{
	std::lock_guard<std::mutex> lk(mutex_getObj);
	if (pInput_obj_ == nullptr) pInput_obj_ = new Input();
	return pInput_obj_;
}

bool Input::getKey(const KeyCode::KeyValue& key){
	//std::lock_guard<std::mutex> lk(pInput_obj_->mutex_getkey_);
	if (pInput_obj_->key_state_map_.find(key) == pInput_obj_->key_state_map_.end()) {
		pInput_obj_->addKey(key);
		return false;
	}
	bool key_state = GET_KEY(key);
	if (pInput_obj_->key_state_map_[key] && key_state) {
		pInput_obj_->key_state_map_[key] = key_state;
		return true;
	}
	pInput_obj_->key_state_map_[key] = key_state;
	return false;
}

bool Input::getKeyDown(const KeyCode::KeyValue& key){
	//std::lock_guard<std::mutex> lk(pInput_obj_->mutex_getkey_);
	if (pInput_obj_->key_state_map_.find(key) == pInput_obj_->key_state_map_.end()) {
		pInput_obj_->addKey(key);
		return false;
	}
	bool key_state = GET_KEY(key);
	if (pInput_obj_->key_state_map_[key] == false && key_state) {
		pInput_obj_->key_state_map_[key] = key_state;
		return true;
	}
	pInput_obj_->key_state_map_[key] = key_state;
	return false;
}

bool Input::getKeyUp(const KeyCode::KeyValue& key){
	//std::lock_guard<std::mutex> lk(pInput_obj_->mutex_getkey_);
	if (pInput_obj_->key_state_map_.find(key) == pInput_obj_->key_state_map_.end()) {
		pInput_obj_->addKey(key);
		return false;
	}
	bool key_state = GET_KEY(key);
	if (pInput_obj_->key_state_map_[key] && key_state == false) {
		pInput_obj_->key_state_map_[key] = key_state;
		return true;
	}
	pInput_obj_->key_state_map_[key] = key_state;
	return false;
}

void Input::addKey(const KeyCode::KeyValue& new_Key){
	key_state_map_.insert(std::pair<char, bool>(new_Key, false));
}

float Input::getAxis(const XAxis::Axis& axis)
{
	return axis == XAxis::Horizontal ? pInput_obj_->getAxisH() : pInput_obj_->getAxisV();
}

void Input::mouseScrollCallback(GLFWwindow* pWindow, double x_offset, double y_offset)
{
	//XENGINE_LOG("Mouse Pos X:" << x_offset << "  Y:" << y_offset);
	pInput_obj_->fMouse_scroll_value_ = (float)y_offset;
	pInput_obj_->bScroll_is_callback_ = true;
}

float Input::getMouseScrollValue()
{
	return pInput_obj_->fMouse_scroll_value_;
}

Vector2 Input::getMousePosTopLeft()
{
	return pInput_obj_->mouse_pos_top_left_;
}

Vector2 Input::getMousePosOrigin()
{
	return pInput_obj_->mouse_pos_origin_;
}

void Input::mousePosCallback(GLFWwindow* pWindow, double x_pos, double y_pos)
{
	//XENGINE_LOG("Mouse Pos X:" << x_pos << "  Y:" << y_pos);
	pInput_obj_->mouse_pos_top_left_.x_ = (float)x_pos;
	pInput_obj_->mouse_pos_top_left_.x_ = (float)y_pos;
	pInput_obj_->mouse_pos_origin_.x_ = (float)x_pos - (XGameViewportSize().x_ / 2.0f);
	pInput_obj_->mouse_pos_origin_.y_ = (XGameViewportSize().y_ / 2.0f) - (float)y_pos;
}


