#include "XImage.h"
#include "ThirdPartyLib/GL/glew.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "CameraManager.h"
#include "XCameraComponent.h"
#include "Material.h"
#include "FrameBuffer.h"
#include "BufferManager.h"
#include "XEngine.h"


XImage::XImage(XGUIBase* pCanvas, const std::string& image_file, const std::string& vertex_file,
	const std::string& fragment_file)
	:pMaterial_(nullptr),XGUIComponentBase(pCanvas),mvo_mat4_(glm::mat4(1.0f))
{
	pMaterial_ = new Material(image_file, vertex_file, fragment_file);
}

XImage::~XImage()
{
	XDELETE_PTR(pMaterial_);
}

void XImage::show()
{
	if (pMaterial_ == nullptr)return;
	if (pMaterial_->pShader_ == nullptr)return;

	mvo_mat4_ = CameraManager::getMainCamera()->getOrthomMat() * CameraManager::getMainCamera()->getViewMat() * getTransMat4();

	pMaterial_->pShader_->enableShader(true);
	pMaterial_->pShader_->setUniformMat4f("mvo_mat4", mvo_mat4_);

	pMaterial_->bindBuffer();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

