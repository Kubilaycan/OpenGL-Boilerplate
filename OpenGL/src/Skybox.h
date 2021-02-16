#pragma once
#include <iostream>
#include "Shader.h"

class Skybox {
private:
	unsigned int m_RendererID;
	int m_height, m_width, m_nrChannels;
	unsigned char* m_data;
	Shader* m_shader;
public:
	Skybox(const std::string& filepath);
	void Draw();
};