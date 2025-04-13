#ifndef XSTATICMESHCOMPONENT_H
#define XSTATICMESHCOMPONENT_H
#include "XComponentBase.h"
#include "XMath.h"
#include <string>

class Shader;
class Texture;
class Material;

class XStaticMeshComponent : public XComponentBase
{
public:
	XStaticMeshComponent(const XTransform& trans, const std::string &material_file, XObject* pBody);
	XStaticMeshComponent(const Vector2& location, const float& rotation, const Vector2& scale,
		const std::string& material_file, XObject* pBody);
	~XStaticMeshComponent();

	void setTexture(Texture* pTex);
	void show() override;
	virtual void begin()override {};
	virtual void run() override {};

	Material* pMaterial_;
private:
	glm::mat4 mvo_mat4_;
	glm::mat4 model_mat4_;
};

#endif

