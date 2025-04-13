#include "FrameBuffer.h"
#include "XEngine.h"
#include "ThirdPartyLib/GL/glew.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &frame_buffer_id_);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id_);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	unBind();
	glDeleteFramebuffers(1, &frame_buffer_id_);
}

void FrameBuffer::attachmentTextrue(const unsigned int& textrue)
{
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textrue, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		XENGINE_LOG("FrameBuffer Incomplete !");
	}
	unBind();
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id_);
}

void FrameBuffer::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
