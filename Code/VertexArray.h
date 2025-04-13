#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

class VertexLayout;
class VertexBuffer;

class VertexArray
{
private:
	unsigned int ver_arr_ID_;

public:
	VertexArray();
	~VertexArray();
	 
	unsigned int getID();
	void bind() const;
	void unBind() const;
	void addLayout(VertexBuffer* const VBO, VertexLayout* const layout);
};

#endif