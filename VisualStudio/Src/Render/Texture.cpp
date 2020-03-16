#include "Texture.h"
#include <glad/glad.h>
#include <stb.h>
#include <iostream>

void Texture::setFlipVerticallyOnLoad(bool mode) {
	stbi_set_flip_vertically_on_load(mode);
}
int Texture::getColorModeFromNrChannels(int nrChannels) {
	switch (nrChannels) {
		case 1: return GL_RED;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4: return GL_RGBA;
		default: return -1;
	}
}

int Texture::DEFAULT_textureWrap_S = GL_REPEAT;
int Texture::DEFAULT_textureWrap_T = GL_REPEAT;
int Texture::DEFAULT_minFilter = GL_NEAREST;
int Texture::DEFAULT_magFilter = GL_NEAREST;

Texture::Texture() {
	colorMode_ = textureType_ = -1;
	width_ = height_ = nrChannels_ = -1;
}
Texture::~Texture() {
	free();
}
void Texture::free() {
	if (ID_ != -1) {
		glDeleteTextures(1, &ID_);
		ID_ = -1;
	}
}

bool Texture::load(const std::string & path, int textureType) {
	if (ID_ != -1) {
		std::cout << "WARINING::TEXTURE::ALREADYLOADED\n" << std::endl;
		loadError(path);
	}
	textureType_ = textureType; //no checking if correct type because not using enums - meh

	//generate buffers
	glGenTextures(1, &ID_);
	glBindTexture(textureType_, ID_);

	//set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(textureType_, GL_TEXTURE_WRAP_S, DEFAULT_textureWrap_S);
	glTexParameteri(textureType_, GL_TEXTURE_WRAP_T, DEFAULT_textureWrap_T);
	glTexParameteri(textureType_, GL_TEXTURE_MIN_FILTER, DEFAULT_minFilter); //GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(textureType_, GL_TEXTURE_MAG_FILTER, DEFAULT_magFilter);

	//unused border color
	float borderColor[] = { 0.9f, 0.3f, 0.6f, 1.0f };
	glTexParameterfv(textureType_, GL_TEXTURE_BORDER_COLOR, borderColor);

	//load and generate the texture
	unsigned char *data = stbi_load(path.c_str(), &width_, &height_, &nrChannels_, 0);

	//load the texture data
	if (data) {
		//save color mode and texture type
		colorMode_ = getColorModeFromNrChannels(nrChannels_);
		if (colorMode_ == -1) {
			stbi_image_free(data);
			std::cout << "EXCEPTION::TEXTURE::CHANNELS\n" << std::endl;
			return loadError(path);
		}

		glTexImage2D(textureType_, 0, colorMode_, width_, height_, 0, colorMode_, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(textureType_);
	}
	else {
		stbi_image_free(data);
		std::cout << "ERROR::TEXTURE::LOADING\n" << std::endl;
		return loadError(path);
	}

	stbi_image_free(data);
	return true;
}
bool Texture::loadError(const std::string & path) const {
	std::cout << path << std::endl;
	std::cout << "/////////////////////////////////////////////////////////////" << std::endl << std::endl;
	return false;
}

void Texture::bind(unsigned int unit) {
	glActiveTexture(GL_TEXTURE0 + unit); //activate the texture unit (0 is default so no need if only 1 unit)
	glBindTexture(textureType_, ID_);
}
void Texture::unbind() {
	glBindTexture(textureType_, 0);
}
