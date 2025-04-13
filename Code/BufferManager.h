#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "VertexLayout.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include <mutex>
#include "XEngine.h"

#define NewBuffer(...) BufferManager::getBufferManagerObj()->newBuffer(__VA_ARGS__)
#define LinkBuffer(...) BufferManager::getBufferManagerObj()->linkBuffer(__VA_ARGS__)
class XObject;


struct ShaderInfoPackage {
	ShaderInfoPackage(Shader*& shader, const std::string& sVer_file, const std::string& sFram_file)
		:shader_(shader), sFram_file_(sFram_file), sVer_file_(sVer_file)
	{}
	Shader*& shader_;
	std::string			sFram_file_;
	std::string			sVer_file_;
};

struct TextureInfoPackage {
	TextureInfoPackage(Texture*& texture, const std::string& file, const int& w, const int& h)
		:w_(w), h_(h), sFile_(file), texture_(texture)
	{}
	int				w_, h_;
	std::string     sFile_;
	Texture*& texture_;
};

struct LinkBufferPackage
{
	LinkBufferPackage(VertexArray*& vao, VertexBuffer*& vbo, VertexLayout*& vl)
		:vao_(vao), vbo_(vbo), vl_(vl)
	{}
	VertexArray*& vao_;
	VertexBuffer*& vbo_;
	VertexLayout*& vl_;
};

template<class T>
struct BufferInfoPackage
{
	BufferInfoPackage(T*& vao) :buffer_type_(vao) {}
	T*& buffer_type_;
};

class BufferManager
{
private:
	BufferManager();

	static BufferManager				*pBuffer_manager_obj_;
	std::mutex							buffer_mutex_;

	
	std::vector<BufferInfoPackage<VertexArray>>			openGLVertexArray_vec_;
	std::vector<BufferInfoPackage<VertexBuffer>>		openGLVertexBuffer_vec_;
	std::vector<BufferInfoPackage<VertexLayout>>		openGLVertexLayout_vec_;
	std::vector<BufferInfoPackage<IndexBuffer>>			openGLIndexBuffer_vec_;
	std::vector<BufferInfoPackage<FrameBuffer>>			openGLFrameBuffer_vec_;
	std::vector<TextureInfoPackage>						openGLTexture_vec_;
	std::vector<ShaderInfoPackage>						openGLShader_vec_;
	std::vector<LinkBufferPackage>						openGLLinkBuffer_vec_;
public:
	~BufferManager();

	static inline BufferManager* getBufferManagerObj() {
		if (pBuffer_manager_obj_ == nullptr) pBuffer_manager_obj_ = new BufferManager();
		return pBuffer_manager_obj_;
	}

	inline void createBuffers() {
		for (auto& temp : openGLVertexArray_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			temp.buffer_type_ = new VertexArray(); 
		}
		for (auto& temp : openGLVertexBuffer_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			temp.buffer_type_ = new VertexBuffer();
		}
		for (auto& temp : openGLVertexLayout_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			temp.buffer_type_ = new VertexLayout();
		}
		for (auto& temp : openGLTexture_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			if (temp.sFile_ == "")
				temp.texture_ = new Texture(temp.w_, temp.h_);
			else temp.texture_ = new Texture(temp.sFile_.c_str());
		}
		for (auto& temp : openGLShader_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			temp.shader_ = new Shader(temp.sVer_file_.c_str(), temp.sFram_file_.c_str());
		}
		for (auto& temp : openGLIndexBuffer_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			temp.buffer_type_ = new IndexBuffer();
		}
		for (auto& temp : openGLLinkBuffer_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			if(temp.vao_ != nullptr)
				temp.vao_->addLayout(temp.vbo_, temp.vl_);
		}
		for (auto& temp : openGLFrameBuffer_vec_)
		{
			std::unique_lock<std::mutex> lk(buffer_mutex_);
			temp.buffer_type_ = new FrameBuffer();
		}
		openGLVertexArray_vec_.clear();
		openGLVertexBuffer_vec_.clear();
		openGLVertexLayout_vec_.clear();
		openGLTexture_vec_.clear();
		openGLShader_vec_.clear();
		openGLIndexBuffer_vec_.clear();
		openGLLinkBuffer_vec_.clear();
		openGLFrameBuffer_vec_.clear();
	}

	inline void newBuffer(VertexArray*& verArr) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLVertexArray_vec_.push_back(verArr);
	}

	inline void newBuffer(VertexBuffer*& verArr) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLVertexBuffer_vec_.push_back(verArr);
	}

	inline void newBuffer(Texture*& texture, const std::string& file, const int& w, const int& h) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLTexture_vec_.push_back(TextureInfoPackage(texture, file, w, h));
	}

	inline void newBuffer(VertexLayout*& verArr) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLVertexLayout_vec_.push_back(verArr);
	}

	inline void newBuffer(Shader*& shader, const std::string& sVer_file = "Resource/VertexShader.vsr", const std::string& sFram_file = "Resource/FragmentShader.fsr") {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLShader_vec_.push_back(ShaderInfoPackage(shader, sVer_file, sFram_file));
	}

	inline void newBuffer(IndexBuffer*& verArr) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLIndexBuffer_vec_.push_back(verArr);
	}

	inline void newBuffer(FrameBuffer*& verArr) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLFrameBuffer_vec_.push_back(verArr);
	}

	inline void linkBuffer(VertexArray*& vao, VertexBuffer*& vbo, VertexLayout*& vl) {
		std::unique_lock<std::mutex> lk(buffer_mutex_);
		openGLLinkBuffer_vec_.push_back(LinkBufferPackage(vao, vbo, vl));
	}
};

#endif