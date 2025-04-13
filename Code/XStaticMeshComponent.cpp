#include "XStaticMeshComponent.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "CameraManager.h"
#include "XCameraComponent.h"
#include "Material.h"
#include "XEngine.h"
#include "BufferManager.h"
#include "ThirdPartyLib/GL/glew.h"



XStaticMeshComponent::XStaticMeshComponent(const XTransform& trans, const std::string &material_file, XObject* pBody)
	:XComponentBase(pBody), pMaterial_(nullptr), mvo_mat4_(glm::mat4(1.0f)),
	model_mat4_(glm::mat4(1.0f))
{
	if (pBody == nullptr)return;
	transform_ = trans;
	pMaterial_ = new Material(material_file);
}

XStaticMeshComponent::XStaticMeshComponent(const Vector2& location, const float& rotation, const Vector2& scale, const std::string& material_file, XObject* pBody)
	:XComponentBase(pBody), pMaterial_(nullptr), mvo_mat4_(glm::mat4(1.0f)),
	model_mat4_(glm::mat4(1.0f))
{
	if (pBody == nullptr)return;
	transform_.location_ = location;
	transform_.rotation_ = rotation;
	transform_.scale_ = scale;
	pMaterial_ = new Material(material_file);
}

XStaticMeshComponent::~XStaticMeshComponent()
{
	pBody_->comp_map_.erase(ull_component_id_);
	XDELETE_PTR(pMaterial_);
}

void XStaticMeshComponent::setTexture(Texture* pTex)
{
	pTex->bind();
}

void XStaticMeshComponent::show()
{
	if (pMaterial_ == nullptr)return;
	if (pMaterial_->pShader_ == nullptr)return;
	if (!pMaterial_->isComplete())return;
	model_mat4_ = getTransMat4();
	mvo_mat4_ = CameraManager::getMainCamera()->getOrthomMat() * CameraManager::getMainCamera()->getViewMat() * model_mat4_;

	pMaterial_->pShader_->enableShader(true);
	pMaterial_->pShader_->setUniformMat4f("mvo_mat4", mvo_mat4_);
	pMaterial_->pShader_->setUniform2f("u_uv_offset", pMaterial_->uv_offset_.x_, pMaterial_->uv_offset_.y_);
	pMaterial_->bindBuffer();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
