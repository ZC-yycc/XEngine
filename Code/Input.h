#ifndef INPUT_H
#define INPUT_H
/*
		输入库
接收用户输入，将键值状态存储在键值对中
*/
#include <conio.h>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include "ThirdPartyLib/GLFW/glfw3.h"
#include <Windows.h>
#include "Transform.h"


#define GET_KEY(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

//规定键码
namespace KeyCode {
	enum KeyValue
	{
		LButton = 1,	RButton, Cancel, MButton, XButton1, XButton2, 
		Back = 8,		Tab, 
		Clear = 12,		Enter,
		Shift = 0x10,	Ctrl, Alt, 
		CapsLock = 20,
		Esc = 27, 
		Space = 0x20,
		Left = 37,		Up, Right, Down,
		Btn_0 = 48,		Btn_1, Btn_2, Btn_3, Btn_4, Btn_5, Btn_6, Btn_7, Btn_8, Btn_9,
		A = 65,			B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
		NumBtn_0 = 96, NumBtn_1, NumBtn_2, NumBtn_3, NumBtn_4, NumBtn_5, NumBtn_6, NumBtn_7, NumBtn_8, NumBtn_9
	};
}
namespace XAxis {
	enum Axis
	{
		Horizontal = 0, Vertical
	};
}
class Input
{
public:
	~Input();
	static Input* getInputObj();
	static bool getKey(const KeyCode::KeyValue &key);
	static bool getKeyDown(const KeyCode::KeyValue& key);
	static bool getKeyUp(const KeyCode::KeyValue& key);

	static float getAxis(const XAxis::Axis& axis);

	static void mousePosCallback(GLFWwindow* pWindow, double x_pos, double y_pos);
	static void mouseScrollCallback(GLFWwindow* pWindow, double x_offset, double y_offset);
	static float getMouseScrollValue();
	static Vector2 getMousePosOrigin();
	static Vector2 getMousePosTopLeft();
private:
	float									fAxis_h_;
	float									fAxis_v_;

private:
	Input();
	void addKey(const KeyCode::KeyValue& new_Key);
	inline float getAxisH() {
		if (GET_KEY(KeyCode::A) || GET_KEY(KeyCode::Left))fAxis_h_ -= 0.05f;
		else if(GET_KEY(KeyCode::D) || GET_KEY(KeyCode::Right)) fAxis_h_ += 0.05f;
		else {
			if (fAxis_h_ >= 0.01f || fAxis_h_ <= -0.01f)
				fAxis_h_ += fAxis_h_ > 0 ? -0.05f : 0.05f;
			else {
				fAxis_h_ = 0;
				return 0.0f;
			}
		}
		if (fAxis_h_ >= 1.0f) fAxis_h_ = 1.0f;
		else if (fAxis_h_ <= -1.0f) fAxis_h_ = -1.0f;
		return fAxis_h_;
	}
	inline float getAxisV() {
		if (GET_KEY(KeyCode::W) || GET_KEY(KeyCode::Up)) fAxis_v_ += 0.05f;
		else if (GET_KEY(KeyCode::S) || GET_KEY(KeyCode::Down)) fAxis_v_ -= 0.05f;
		else {
			if (fAxis_v_ >= 0.01f ||fAxis_v_ <= -0.01f)
				fAxis_v_ += fAxis_v_ > 0 ? -0.05f : 0.05f;
			else {
				fAxis_v_ = 0;
				return 0.0f;
			}
		}
		if (fAxis_v_ >= 1.0f) fAxis_v_ = 1.0f;
		else if (fAxis_v_ <= -1.0f) fAxis_v_ = -1.0f;
		return fAxis_v_;
	}
private:
	std::mutex								mutex_getkey_;
	std::unordered_map<char, bool>			key_state_map_;
	float									fMouse_scroll_value_;
	bool									bScroll_is_callback_;
	Vector2									mouse_pos_origin_;
	Vector2									mouse_pos_top_left_;
	static Input							*pInput_obj_;
};
#endif
