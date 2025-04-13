#include "VertexBuffer.h"
#include "ThirdPartyLib/GL/glew.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &ver_buff_ID_);
	glBindBuffer(GL_ARRAY_BUFFER, ver_buff_ID_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
	unBind();
}

VertexBuffer::~VertexBuffer(){
	unBind();
	glDeleteBuffers(1, &ver_buff_ID_);
}

void VertexBuffer::bind()const {
	glBindBuffer(GL_ARRAY_BUFFER, ver_buff_ID_);
}

void VertexBuffer::unBind()const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
