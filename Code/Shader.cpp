#include "Shader.h"
#include "ThirdPartyLib/GL/glew.h"
#include "ThirdPartyLib/GLFW/glfw3.h"
#include "DebugLog.h"

Shader::Shader(const std::string& vertex_file, const std::string& fragment_file)
{
	vertex_file_.open(vertex_file);
	fragment_file_.open(fragment_file);
	
	ver_shader_stream_ << vertex_file_.rdbuf();
	frag_shader_stream_ << fragment_file_.rdbuf();

	vertex_file_.close();
	fragment_file_.close();

	unsigned int vertex_shader_ID;
	unsigned int fragment_shader_ID;

	std::string ver_shader_code_temp = ver_shader_stream_.str();
	std::string frag_shader_code_temp = frag_shader_stream_.str();

	const char* ver_shader_code = ver_shader_code_temp.c_str();
	const char* frag_shader_code = frag_shader_code_temp.c_str();

	int success = 0;
	char infoLog[512] = { 0 };
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_ID, 1, &ver_shader_code, nullptr);
	glCompileShader(vertex_shader_ID);
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader_ID, 512, nullptr, infoLog);
		XENGINE_LOG("ERROR::shader::vertex::COMPILATION_FAILED\n");
		XENGINE_LOG(infoLog);
	};

	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_ID, 1, &frag_shader_code, nullptr);
	glCompileShader(fragment_shader_ID);
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader_ID, 512, nullptr, infoLog);
		XENGINE_LOG("ERROR::shader::fragment::COMPILATION_FAILED\n");
		XENGINE_LOG(infoLog);
	};

	shader_ID_ = glCreateProgram();
	glAttachShader(shader_ID_, vertex_shader_ID);
	glAttachShader(shader_ID_, fragment_shader_ID);
	glLinkProgram(shader_ID_);
	glGetShaderiv(shader_ID_, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_ID_, 512, nullptr, infoLog);
		XENGINE_LOG("ERROR::shader::COMPILATION_FAILED\n");
		XENGINE_LOG(infoLog);
	};

	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);
}

Shader::~Shader(){
	glDeleteShader(shader_ID_);
}

void Shader::enableShader(bool enable){
	enable ?
		glUseProgram(shader_ID_) : glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, const int& value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, const float& value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string &name, const float &vec_00, const float &vec_01, const float &vec_02, const float &vec_03){

	glUniform4f(getUniformLocation(name), vec_00, vec_01, vec_02, vec_03);
}

void Shader::setUniform2f(const std::string& name, const float& vec_00, const float& vec_01)
{
	glUniform2f(getUniformLocation(name), vec_00, vec_01);
}

void Shader::setUniform3f(const std::string& name, const float& vec_00, const float& vec_01, const float& vec_02)
{
	glUniform3f(getUniformLocation(name), vec_00, vec_01, vec_02);
}

void Shader::setUniformMat4f(const std::string &uniform_name, const glm::mat4 &pMat4)
{
	glUniformMatrix4fv(getUniformLocation(uniform_name), 1, GL_FALSE, &pMat4[0][0]);
}

int Shader::getUniformLocation(const std::string &unform_name)
{
	if (uniform_location_temp_.find(unform_name) != uniform_location_temp_.end()) {
		return uniform_location_temp_[unform_name];
	}
	int location = glGetUniformLocation(shader_ID_, unform_name.c_str());
	if (location == -1) {
		std::cout << "locationÎ´ÕÒµ½" << std::endl;
		return -1;
	}
	uniform_location_temp_[unform_name] = location;
	return location;
}

