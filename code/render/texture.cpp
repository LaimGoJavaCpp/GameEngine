#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string& name)
{
	sprite = loadSprite("../res/images/" + name + ".png");
}

Texture::~Texture()
{
	glDeleteTextures(1,&sprite);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite);
}

GLuint Texture::loadSprite(const std::string& path)
{
	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
	{
		std::cout << "failed to load your sprite!";
		std::exit(-1);
	}

	//иницальзацыя текстуры
	GLuint texture = 0;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//настройка текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//загрузка текстуры
	if (nrChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "мне лень что-то тут писать но короче нет такого nrChannels так что дебаж";
		std::exit(-1);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	//освобождаем память
	STBI_FREE(data);

	return texture;
}  