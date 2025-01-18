#pragma once

#include <fstream>
#include <string>
#include <GL/glew.h>

namespace GL
{
	class Program
	{
	public:
		Program(const std::string& name);
		~Program();
		void link();
		void bindAttribute(GLuint index, const std::string& name);
		void use();
		void loadUniform(const std::string& name, double value);
		GLint getProgram() { return mGlProgram; }
	private:
		GLint loadShader(const std::string& path, GLenum shaderType);
		GLint mGlProgram;
		GLuint mVertex;
		GLuint mFragment;
	};
}