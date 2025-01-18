#pragma once

#include <gl/glew.h>
#include <vector>

namespace GL
{
	class VAO
	{
	public:
		VAO();
		VAO(const VAO&) = delete;
		~VAO();
		void bind();
		void addVertexBufferObject(const std::vector<float>& data);
		void draw(GLsizei sizei);
	private:
		GLuint mVAO;
		std::vector<GLuint> mBuffers;
	};
}