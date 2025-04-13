#include "XBlur.h"
#include "FrameBuffer.h"
#include "SceneManager.h"
#include "Material.h"
#include "BufferManager.h"
#include "ThirdPartyLib/GL/glew.h"
#include "Texture.h"
#include "CameraManager.h"
#include "GameSettings.h"
#include "Shader.h"


XBlur::XBlur(XGUIBase* pCanvas, const Vector2& location, const Vector2& scale)
	:XGUIComponentBase(pCanvas), pScene_(nullptr), pMaterial_(nullptr), fBlur_intensity_(2.0f)
{
	//NewBuffer(pSource_);
	//NewBuffer(pGaussian_blur_);
	//NewBuffer(pGaussian_blur_texture_, "", XGameViewportSize().x_, XGameViewportSize().y_);
	pScene_ = SceneManager::getSceneManagerObj();
	transform_center_.scale_ = scale;
	transform_center_.location_ = location;
	pMaterial_ = new Material(XGameViewportSize().x_, XGameViewportSize().y_,"Resource/BlurShader.vsr", "Resource/GaussianBlur.fsr");
}

XBlur::~XBlur()
{
	XDELETE_PTR(pSource_);
	XDELETE_PTR(pMaterial_);
	XDELETE_PTR(pGaussian_blur_);
	XDELETE_PTR(pGaussian_blur_texture_);
}

void XBlur::show()
{
	if (pMaterial_ == nullptr)return;
	if (pMaterial_->pTexture_ == nullptr) return;
	if (pGaussian_blur_texture_ == nullptr) return;
	mvo_mat4_ = CameraManager::getMainCamera()->getOrthomMat() * getTransMat4();
	pSource_->attachmentTextrue(pMaterial_->pTexture_->texture_ID_);
	pGaussian_blur_->attachmentTextrue(pGaussian_blur_texture_->texture_ID_);

	pSource_->bind();
	glViewport(
		(int)( - transform_center_.location_.x_ - (XGameViewportSize().x_ / 2) + (transform_center_.scale_.x_ * 10)),
		(int)( - transform_center_.location_.y_ - (XGameViewportSize().y_ / 2) + (transform_center_.scale_.y_ * 10)),
		(int)XGameViewportSize().x_, 
		(int)XGameViewportSize().y_
	);
	pScene_->postProcessing();
	pSource_->unBind();


	pMaterial_->pShader_->enableShader(true);
	pMaterial_->pShader_->setUniform1f("blur_offset", fBlur_intensity_);
	pMaterial_->pShader_->setUniform1i("horizontal", false);
	pMaterial_->pShader_->setUniformMat4f("mvo_mat4", mvo_mat4_);
	pMaterial_->pShader_->setUniform2f("region",
		transform_center_.scale_.x_ * 20 / (int)XGameViewportSize().x_,
		transform_center_.scale_.y_ * 20 / (int)XGameViewportSize().y_);

	pMaterial_->bindBuffer();
	pGaussian_blur_->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	pGaussian_blur_->unBind();
	glViewport(0, 0, (int)XGameViewportSize().x_, (int)XGameViewportSize().y_);

	pMaterial_->pShader_->setUniform1i("horizontal", true);
	pGaussian_blur_texture_->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
