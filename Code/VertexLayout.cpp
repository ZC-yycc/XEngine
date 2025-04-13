#include "VertexLayout.h"
#include "ThirdPartyLib/GL/glew.h"

VertexLayout::VertexLayout() :
	stride_(0)
{
	addVertexAttribute<float>(2);
	addVertexAttribute<float>(2);
}

template<>
void VertexLayout::addVertexAttribute<float>(int AttributeCount){
	vec_attr_.push_back({ GL_FLOAT,GL_FALSE,AttributeCount});
	stride_ += AttributeCount * sizeof(float);
}