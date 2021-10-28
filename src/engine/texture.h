#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

#include <glm/glm.hpp>

#include <iostream>
#include <string>


struct Texture {

	GLuint textureID;
	glm::vec4 color;
	int width, height, bpp;

	Texture(GLuint textureID, glm::vec4 color, int width, int height, int bpp)
	: textureID(textureID), color(color), width(width), height(height), bpp(bpp) {}
};


Texture* loadTexture(const std::string& filepath);

