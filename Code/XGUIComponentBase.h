#ifndef GUICOMPONENTBASE_H
#define GUICOMPONENTBASE_H
#include "XMath.h"
#include "Transform.h"

class XGUIBase;

class XGUIComponentBase
{
public:
	XGUIComponentBase(XGUIBase *pCanvas);
	virtual ~XGUIComponentBase();

	virtual void show() = 0;
	virtual void run() {};
	inline size_t getID() const {
		return ull_id_;
	}

	inline void setID(const size_t& ull_id) {
		ull_id_ = ull_id;
	}

	inline void enable(bool isEnable) {
		bEnable_ = isEnable;
	}
	
	inline bool getState()const {
		return bEnable_;
	}
	glm::mat4 getTransMat4();
public:
	XTransform				transform_anchors_;
	XTransform				transform_center_;
	glm::mat4				trans_mat4_;
private:
	bool					bEnable_;
	size_t					ull_id_;
	XGUIBase				*pCanvas_;
};

#endif

