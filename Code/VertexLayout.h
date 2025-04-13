#ifndef LAYOUT_AND_ATTRIBUTE
#define LAYOUT_AND_ATTRIBUTE
#include <vector>

struct VertexAttribute
{
public:
	unsigned int		type;
	unsigned char		Normal;
	int					count;
};

class VertexLayout
{
public:
	std::vector<VertexAttribute>	vec_attr_;
	unsigned int					stride_;
public:
	VertexLayout();

	template<class TempType>
	void addVertexAttribute(int AttributeCount);


	template<>
	void addVertexAttribute<float>(int AttributeCount);

};

#endif

