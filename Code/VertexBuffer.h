#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


class VertexBuffer {
	
public:

	unsigned int ver_buff_ID_;
	float vertexs[16] = {
		 1.0f,  1.0f,  1.0, 1.0,
		 1.0f, -1.0f,  1.0, 0.0,
		-1.0f, -1.0f,  0.0, 0.0,
		-1.0f,  1.0f,  0.0, 1.0
	};
public:
	VertexBuffer();
	~VertexBuffer();
	void bind()const;
	void unBind()const;
};

#endif // !

