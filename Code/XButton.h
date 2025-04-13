#ifndef XBUTTON_H
#define XBUTTON_H
#include "XGUIComponentBase.h"
#include <functional>
#include <string>

#define XOnClick(F) bindOnclick(this, F);
#define XOnMouseHang(F) bindOnMouseHang(this, F);
#define XOnMouseOut(F) bindOnMouseOut(this, F);
#define XOnMouseEnter(F) bindOnMouseEnter(this, F);

class XImage;
class XGUIBase;

class XButton : public XGUIComponentBase
{
public:
	XButton(XGUIBase *pCanvas, const std::string &click_file = "Resource/red.png",
		const std::string& hang_file = "Resource/emojis.png",
		const std::string& gene_file = "Resource/Cube_m.png");
	~XButton();
	void show()override;
	void run()override;
	template<class T>
	void bindOnclick(T* obj, void(T::*func)()) {
		onclick_func_ = std::bind(func, obj);
	}
	template<class T>
	void bindOnMouseHang(T* obj, void(T::* func)()) {
		hang_func_ = std::bind(func, obj);
	}
	template<class T>
	void bindOnMouseEnter(T* obj, void(T::* func)()) {
		onBtn_enter_ = std::bind(func, obj);
	}
	template<class T>
	void bindOnMouseOut(T* obj, void(T::* func)()) {
		onBtn_out_ = std::bind(func, obj);
	}
private:
	void transUpdate();
private:
	XImage							*pImage_hang_;
	XImage							*pImage_general_;
	XImage							*pImage_click_;

	std::function<void()>			onclick_func_;
	std::function<void()>			hang_func_;
	std::function<void()>			onBtn_enter_;
	std::function<void()>			onBtn_out_;

	float							fHalf_length_;
	float							fHalf_width_;
	float							fLeft_border_;
	float							fRight_border_;
	float							fUp_border_;
	float							fDown_border_;

	bool							bMouse_last_state_;
};

#endif