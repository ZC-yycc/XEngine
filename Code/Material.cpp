#include "Material.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexLayout.h"
#include "FrameBuffer.h"
#include "BufferManager.h"

Material::Material(const std::string &material_file, const std::string& vertex_file,const std::string& fragment_file)
{
	uv_offset_ = Vector2(0.0, 0.0f);
	NewBuffer(pVertex_array_);
	NewBuffer(pVertex_buffer_);
	NewBuffer(pShader_, vertex_file.c_str(), fragment_file.c_str());
	NewBuffer(pIndex_buffer_);
	NewBuffer(pTexture_, material_file.c_str(),0,0);
	NewBuffer(pVertex_layout_);

	LinkBuffer(pVertex_array_, pVertex_buffer_, pVertex_layout_);
}

Material::Material(const int& w, const int& h, const std::string& vertex_file, const std::string& fragment_file)
{
	uv_offset_ = Vector2(0.0, 0.0f);
	NewBuffer(pVertex_array_);
	NewBuffer(pVertex_buffer_);
	NewBuffer(pShader_, vertex_file.c_str(), fragment_file.c_str());
	NewBuffer(pIndex_buffer_);
	NewBuffer(pTexture_, "", w, h);
	NewBuffer(pVertex_layout_);

	LinkBuffer(pVertex_array_, pVertex_buffer_, pVertex_layout_);
}

Material::~Material()
{
	XDELETE_PTR(pVertex_array_);
	XDELETE_PTR(pVertex_buffer_);
	XDELETE_PTR(pShader_);
	XDELETE_PTR(pIndex_buffer_);
	XDELETE_PTR(pVertex_layout_);
	XDELETE_PTR(pTexture_);
}

void Material::bindBuffer() const
{
	pTexture_->bind();
	pVertex_array_->bind();
	pIndex_buffer_->bind();
}