#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Camera;

class Window
{
public:
	Window(std::string title, int width, int height);
	~Window();

	void loop();

private:
	GLFWwindow* window;
	Camera* cam;
};