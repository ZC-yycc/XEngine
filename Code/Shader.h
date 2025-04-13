#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "XMath.h"

class Shader {

public:
	unsigned int							shader_ID_;
	std::stringstream						ver_shader_stream_;
	std::stringstream						frag_shader_stream_;
	std::ifstream							vertex_file_;
	std::ifstream							fragment_file_;
	std::unordered_map<std::string,int>		uniform_location_temp_;

public:
	Shader(const std::string &vertex_file, const std::string& fragment_file);
	~Shader();

	void enableShader(bool enable);
	void setUniform1i(const std::string& name, const int& value);
	void setUniform1f(const std::string& name, const float& value);
	void setUniform2f(const std::string& name, const float& vec_00, const float& vec_01);
	void setUniform3f(const std::string& name, const float& vec_00, const float& vec_01, const float& vec_02);
	void setUniform4f(const std::string &name, const float& vec_00, const float& vec_01, const float& vec_02, const float& vec_03);
	void setUniformMat4f(const std::string &uniform_name, const glm::mat4 &pMat4);

private:
	int getUniformLocation(const std::string &unform_name);
};

#endif // !SHADER_H

