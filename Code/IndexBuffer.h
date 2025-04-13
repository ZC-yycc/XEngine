#ifndef INDEXUFFER_H
#define INDEXUFFER_H

class IndexBuffer {
	
public:

	unsigned int index_buff_ID_;

	unsigned int index[6] = {
		0, 3, 1, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
public:
	IndexBuffer();
	~IndexBuffer();
	void bind()const;
	void unBind()const;

};

#endif // !

