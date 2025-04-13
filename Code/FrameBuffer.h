#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void attachmentTextrue(const unsigned int& textrue);
	void bind();
	void unBind();

	unsigned int	frame_buffer_id_;
};

#endif