#pragma once

#include <string>
#include <unordered_map>
#include<GL/glew.h>
#include "glm/glm.hpp"

struct ShaderSource
{
	std::string Vertex;
	std::string Fragment;
};

class Shader {
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Uniform stuff
	
	template<typename T>
	void SetUniform(const std::string& name, T value) {
		std::cout << "No uniform type" << std::endl;
	}
	
	template<>
	void SetUniform<int>(const std::string& name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}
	template <>
	void SetUniform<glm::vec4>(const std::string& name, glm::vec4 value) {
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	template<>
	void SetUniform<glm::mat4>(const std::string& name, glm::mat4 value) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}
	

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	ShaderSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(GLenum type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
