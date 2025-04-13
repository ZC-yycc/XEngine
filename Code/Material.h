#ifndef DEFAULTMESHINFO
#define DEFAULTMESHINFO

#include "Transform.h"
#include "XEngine.h"

class VertexArray;
class VertexBuffer;
class Shader;
class IndexBuffer;
class Texture;
class VertexLayout;
class FrameBuffer;

class Material
{
public:
	Material(const std::string &material_file, const std::string &vertex_file = "Resource/VertexShader.vsr",
		const std::string &fragment_file = "Resource/FragmentShader.fsr");
	Material(const int &w,const int &h, const std::string& vertex_file = "Resource/VertexShader.vsr",
		const std::string& fragment_file = "Resource/FragmentShader.fsr");
	~Material();

	void bindBuffer() const;
	inline bool isComplete() {
		return (pVertex_array_ || pVertex_buffer_ ||
			pIndex_buffer_ || pVertex_layout_);
	}
private:
	VertexArray		*pVertex_array_;
	VertexBuffer	*pVertex_buffer_;
	IndexBuffer		*pIndex_buffer_;
	VertexLayout	*pVertex_layout_;
	
public:
	Shader			*pShader_;
	Texture			*pTexture_;
	Vector2			uv_offset_;
};


#endif 