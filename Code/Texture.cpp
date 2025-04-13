#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
#include "ThirdPartyLib/GL/glew.h"
#include "DebugLog.h"

Texture::Texture(const unsigned int& w, const unsigned int& h)
	:nWidth_(w), nHeight_(h), texture_ID_(0)
{
	wrap_mode_ = XTextureWrapping::REPEAT;
	glGenTextures(1, &texture_ID_);
	glBindTexture(GL_TEXTURE_2D, texture_ID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth_, nHeight_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}

Texture::Texture(const char* file)
{
	wrap_mode_ = XTextureWrapping::REPEAT;
	glGenTextures(1, &texture_ID_);
	glBindTexture(GL_TEXTURE_2D, texture_ID_);
	stbi_set_flip_vertically_on_load(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data = stbi_load(file,&nWidth_,&nHeight_,&nrChannels_,0);
	if (data != nullptr) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth_, nHeight_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//生成多级纹理
	}
	else {
		XENGINE_LOG("纹理加载错误\n");
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	unBind();
	glDeleteTextures(1, &texture_ID_);
}


void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, texture_ID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode_);
}

void Texture::unBind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
