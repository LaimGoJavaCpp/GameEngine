#include "Program.hpp"
#include <iostream>

GL::Program::Program(const std::string& name)
{
	mGlProgram = glCreateProgram();
	mVertex = loadShader("../res/shaders/" + name + ".vert", GL_VERTEX_SHADER);
	mFragment = loadShader("../res/shaders/" + name + ".frag", GL_FRAGMENT_SHADER);
}

GL::Program::~Program()
{
	glDeleteProgram(mGlProgram);
}

GLint GL::Program::loadShader(const std::string& path, GLenum shaderType)
{
	GLint shader = glCreateShader(shaderType);
	std::ifstream fis(path);
	std::string shaderCode = { std::istreambuf_iterator<char>(fis), std::istreambuf_iterator<char>() };
	const char* c = shaderCode.c_str();
	glShaderSource(shader, 1, &c, nullptr);
	glCompileShader(shader);
	{ // проверка ошибок
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			char buf[0x1000];
			GLsizei len;
			glGetShaderInfoLog(shader, 0x1000, &len, buf);
			if (len > 0)
			{
				std::cout << "failed to compiled shader:( : " << path << std::endl << buf;
				std::exit(-1);
			}
		}
	}
	return shader;
}

void GL::Program::link()
{
	glAttachShader(mGlProgram, mVertex);
	glAttachShader(mGlProgram, mFragment);
	glLinkProgram(mGlProgram);
}

void GL::Program::bindAttribute(GLuint index, const std::string& name)
{
	//glVertexAttribPointer(0, sizeof(float) * 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glBindAttribLocation(mGlProgram, index, name.c_str());
}

void GL::Program::use()
{
	glUseProgram(mGlProgram);
}

void GL::Program::loadUniform(const std::string& name, double value)
{
	auto loc = glGetUniformLocation(mGlProgram, name.c_str());
	float outVal = static_cast<float>(value);
	glUniform1f(loc, outVal);
}
