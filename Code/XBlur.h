#ifndef XBLUR_H
#define XBLUR_H
#include "XGUIComponentBase.h"
#include "XMath.h"
class FrameBuffer;
class SceneManager;
class Material;
class Texture;

class XBlur : public XGUIComponentBase
{
public:
	XBlur(XGUIBase* pCanvas, const Vector2& location = { 0, 0 },
		const Vector2& scale = { 10.0f, 10.0f });
	~XBlur();
public:
	float					fBlur_intensity_;
private:
	FrameBuffer				*pSource_;
	FrameBuffer				*pGaussian_blur_;
	Texture					*pGaussian_blur_texture_;

	SceneManager			*pScene_;
	Material				*pMaterial_;

	glm::mat4				mvo_mat4_;

	void show()override;
};
#endif
