#include "VAO.hpp"

GL::VAO::VAO()
{
	glGenVertexArrays(1, &mVAO);
	bind();
}

GL::VAO::~VAO()
{
	glDeleteBuffers(mBuffers.size(), mBuffers.data());
	glDeleteVertexArrays(1,&mVAO);
}

void GL::VAO::bind()
{
	glBindVertexArray(mVAO);
}

void GL::VAO::addVertexBufferObject(const std::vector<float>& data)
{
	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	const uint64_t offset = 3 * sizeof(float);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)offset);
	glEnableVertexAttribArray(1);
	mBuffers.push_back(vbo);
}

void GL::VAO::draw(GLsizei sizei)
{
	for (size_t i = 0; i < 2; ++i)
	{
		glEnableVertexAttribArray(i);
	}
	bind();
	glDrawArrays(GL_TRIANGLES,0,sizei);
	for (size_t i = 0; i < 2; ++i)
	{
		glDisableVertexAttribArray(i);
	}
}