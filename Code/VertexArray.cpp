#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "ThirdPartyLib/GL/glew.h"



VertexArray::VertexArray(){
	glGenVertexArrays(1, &ver_arr_ID_);
	glBindVertexArray(ver_arr_ID_);
	unBind();
}

VertexArray::~VertexArray(){
	unBind();
	glDeleteVertexArrays(1,&ver_arr_ID_);
}

unsigned int VertexArray::getID(){
	return ver_arr_ID_;
}

void VertexArray::bind() const{
	glBindVertexArray(ver_arr_ID_);
}

void VertexArray::unBind() const{
	glBindVertexArray(0);
}

void VertexArray::addLayout(VertexBuffer* const VBO, VertexLayout* const layout){
	bind();
	VBO->bind();
	const auto &attribs = layout->vec_attr_;
	unsigned int Offset = 0;
	for (size_t i = 0; i < attribs.size(); i++)
	{
		glVertexAttribPointer(i, attribs[i].count, attribs[i].type,
			attribs[i].Normal, layout->stride_, (void*)Offset);
		glEnableVertexAttribArray(i);
		Offset += attribs[i].count * sizeof(attribs[i].type);
	}
	VBO->unBind();
	unBind();
}
