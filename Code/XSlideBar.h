#ifndef XSLIDEBAR_H
#define XSLIDEBAR_H
#include "XGUIComponentBase.h"
#include "XEngine.h"

#ifndef SLIDEBARCALLBACK
#define SLIDEBARCALLBACK
#define XValueChangeEvent(F) bindValueChangeCallback(this, F);
#define XValueMaxChangeEvent(F) bindValueMaxCallback(this, F);
#define XValueMinChangeEvent(F) bindValueMinCallback(this, F);
#endif
class XImage;

class XSlideBar : public XGUIComponentBase
{
public:
	XSlideBar(XGUIBase* pCanvas, const Vector2& scale = Vector2(10, 1), 
		const std::string& sBackground_file = "Resource/Cube_m.png",
		const std::string& sStrip_file = "Resource/red.png", const float& value = 0.3f);
	~XSlideBar();
	void show()override;
	void run()override;
	inline void setRange(const float& min, const float& max) {
		if (max < min) {
			XENGINE_LOG("XSlideBar::setRange : max < min");
			return;
		}
		fMax_ = max; fMin_ = min;
	}
	inline float getValue() const {
		return fValue_;
	}
	inline Vector2 getRange() const {
		return { fMin_,fMax_ };
	}
	inline Vector2 getScale() const {
		return scale_;
	}

	template<class T>
	void bindValueChangeCallback(T *obj,void(T::*fun)(const float&)) {
		value_change_callback_ = std::bind(fun, obj, std::placeholders::_1);
	}
	template<class T>
	void bindValueMinCallback(T* obj, void(T::* fun)()) {
		value_min_callback_ = std::bind(fun, obj);
	}
	template<class T>
	void bindValueMaxCallback(T* obj, void(T::* fun)()) {
		value_max_callback_ = std::bind(fun, obj);
	}
private:
	XImage				*pBackground_;
	XImage				*pStrip_;
	Vector2				scale_;

	float				fLast_value_;
	float				fMax_;
	float				fMin_;

	std::function<void(const float&)>	value_change_callback_;
	std::function<void()>				value_min_callback_;
	std::function<void()>				value_max_callback_;
public:
	float				fValue_;
};

#endif
