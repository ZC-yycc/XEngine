#include "IndexBuffer.h"
#include "ThirdPartyLib/GL/glew.h"

IndexBuffer::IndexBuffer(){
	glGenBuffers(1, &index_buff_ID_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buff_ID_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	unBind();
}

IndexBuffer::~IndexBuffer(){
	unBind();
	glDeleteBuffers(1,&index_buff_ID_);
}

void IndexBuffer::bind()const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buff_ID_);
}

void IndexBuffer::unBind()const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
