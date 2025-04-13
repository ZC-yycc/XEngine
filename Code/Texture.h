#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameSettings.h"


namespace XTextureWrapping {
	enum WraparoundMethod
	{
		REPEAT = 0x2901,
		MIRRORED_REPEAT = 0x8370,
		CLAMP_TO_EDGE = 0x812F,
		CLAMP_TO_BORDER = 0x812D
	};
}

class Texture
{
public:
	unsigned int						texture_ID_;
	int									nWidth_, nHeight_, nrChannels_;
	XTextureWrapping::WraparoundMethod	wrap_mode_;
public:
	Texture(const unsigned int& w, const unsigned int& h);
	Texture(const char* file);
	~Texture();
	void bind();
	void unBind();

};

#endif
