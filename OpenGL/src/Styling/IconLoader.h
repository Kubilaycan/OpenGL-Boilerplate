#pragma once

#include <iostream>
#include <stb_image/stb_image.h>
#include <GLFW/glfw3.h>


static GLFWimage load_icon(const std::string& filepath) {
	GLFWimage image;
	int bpp;
	image.pixels = stbi_load(filepath.c_str(), &image.width, &image.height, &bpp, 4);
	return image;
}

void SetWindowIcon(GLFWwindow* window, const std::string& filepath) {
	GLFWimage images[2];
	images[0] = load_icon(filepath);
	images[1] = load_icon(filepath);
	glfwSetWindowIcon(window, 2, images);
}