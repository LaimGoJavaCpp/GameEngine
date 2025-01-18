#pragma once

#include "GL/glew.h"

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();
	void bind();
private:
	GLuint loadSprite(const std::string& path);
	GLuint sprite;
};