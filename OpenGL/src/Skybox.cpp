#include "Skybox.h"
#include <GL/glew.h>
#include <stb_image/stb_image.h>
#include <string>
#include <thread>


Skybox::Skybox(const std::string& filepath):
	m_RendererID(0)
{
	this->m_shader = new Shader("resources/shaders/Skybox.shader");
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	for (int i = 0; i < 6; i++) {
		std::string valid_path = filepath + "/" + std::to_string(i+1) + ".png";
		std::cout << valid_path << std::endl;
		m_data = stbi_load(valid_path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
		if (m_data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
			stbi_image_free(m_data);
		}
		else {
			std::cout << "Incorrect skybox path:" << valid_path << std::endl;
		}
	}
	//std::thread loader(&Skybox::loadImageAsync, this, filepath);
	//loader.join();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::Draw()
{
	glDepthMask(GL_FALSE);
	m_shader->Bind();
	//glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	m_shader->Unbind();
}
/*
void Skybox::loadImages(const std::string & path)
{
	for (int i = 0; i < 6; i++) {
		std::string valid_path = path + "/" + std::to_string(i + 1) + ".png";
		m_data = stbi_load(valid_path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
		if (m_data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
			stbi_image_free(m_data);
		}
		else {
			std::cout << "Incorrect skybox path:" << valid_path << std::endl;
		}
	}
}
*/