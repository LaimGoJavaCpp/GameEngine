#include "Window.hpp"
#include "GLFW.hpp"

int main(int argc, char** argv)
{
	Init_GLFW();

	Window* window = new Window("Engine", 640,480);

	window->loop();

	delete window;
	
	return 0;
}