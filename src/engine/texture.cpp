#include "texture.h"


Texture* loadTexture(const std::string& filepath) {
	
	GLuint textureID;
	int width, height, bpp;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(localBuffer);

	return new Texture(textureID, {1.0f, 1.0f, 1.0f, 1.0f}, width, height, bpp);
}
