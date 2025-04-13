#ifndef XIMAGE_H
#define XIMAGE_H
#include <string>
#include "XGUIComponentBase.h"
#include "XMath.h"

class Material;

class XImage : public XGUIComponentBase
{
public:
	XImage(XGUIBase *pCanvas, const std::string &image_file = "Resource/Cube_m.png",
		const std::string& vertex_file = "Resource/VertexShader.vsr",
		const std::string& fragment_file = "Resource/FragmentShader.fsr");
	virtual ~XImage();
public:
	virtual void show()override;

public:
	Material* pMaterial_;
protected:
	glm::mat4 mvo_mat4_;
};

#endif

