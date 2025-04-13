#ifndef XMATH_H
#define XMATH_H

#include "ThirdPartyLib/glm-master/glm/glm.hpp"
#include "ThirdPartyLib/glm-master/glm/gtc/matrix_transform.hpp"
#include "ThirdPartyLib/glm-master/glm/gtc/type_ptr.hpp"
#include <random>
#include <chrono>

#define XPI 3.1415926f

class XMath
{
public:
	static int randInt(const int& lower_limit, const int& upper_limit) {
		return (rand() % (upper_limit - lower_limit)) + lower_limit;
	}
	static float randFloat(const float& lower_limit, const float& upper_limit) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(lower_limit, upper_limit);

		return dis(gen);
	}
};
#endif