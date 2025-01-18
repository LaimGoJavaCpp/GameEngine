#include "GLFW.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

void Init_GLFW()
{
	if (!glfwInit())
	{
		std::cout << "glfw not init!";
		std::exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}