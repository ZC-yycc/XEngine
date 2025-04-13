#ifndef CANVAS_H
#define CANVAS_H
#include "XGUIBase.h"

class XImage;
class XButton;
class XBlur;
class XSlideBar;

class Canvas : public XGUIBase
{
public:
	Canvas();
	void run()override;
	void onclick();
	void onMouseHang();
	void onMouseEnter();
	void onMouseOut();
public:
	XSlideBar* pSlide_;
	//XButton			*pButton_;
	//XImage			*pImage_;
	XBlur* pBlur_;
};
#endif
