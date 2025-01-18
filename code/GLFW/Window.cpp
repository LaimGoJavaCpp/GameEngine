#include "Window.hpp"
#include "VAO.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Window::Window(std::string title, int width, int height)	
{
	cam = new Camera({ 5.f, 0.f, 5.f });
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window)
	{
		std::cout << "window not init!";
		glfwTerminate();
		std::exit(-1);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "glew not init!";
		glfwTerminate();
		std::exit(-1);
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::loop()
{
	GL::VAO vao;
	vao.addVertexBufferObject({
	//0.5f,  0.5f,  0, 1.f, 0.f,
	//-0.5f,  0.5f,  0, 0.f, 0.f,
	//-0.5f, -0.5f, 0, 0.f, 1.f,

	//0.5f,  0.5f,  0, 1.f, 0.f,
	//-0.5f, -0.5f, 0, 0.f, 1.f,
	//0.5f, -0.5f, 0, 1.f, 1.f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		});

	GL::Program shader("image");
	
	shader.link();
	shader.use();

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 1000.0f);

	Texture sprite("crp"); 
	sprite.bind();

	glm::vec3 lookPoint { 0.f, 0.f, -1.f };
	const glm::vec3 up{0.f, 1.f, 0.f};
	double delta = 0.f;
	while (!glfwWindowShouldClose(window))
	{
		double beginFrameTime = glfwGetTime();

		glm::vec3 direction = glm::normalize(lookPoint - cam->getCamPosition());
		glm::vec3 side = glm::cross(direction, up);
		
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cam->setPosition(cam->getCamPosition() - glm::vec3(-0.01f,0,0)); //camPosition += (-side * 50.f * (float)delta);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			cam->setPosition(cam->getCamPosition() - glm::vec3(0.01f, 0, 0));
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		
		shader.use();
		sprite.bind();

		GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
		GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
		GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");

		glm::mat4 model(1.f);
		model = glm::scale(model, glm::vec3{ 2.f, 2.f, 2.f });
		model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
		model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		cam->setViev(glm::lookAt(cam->getCamPosition(), lookPoint, up));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam->getView()));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		vao.draw(36);
		glfwPollEvents();
		glfwSwapBuffers(window);

		delta = glfwGetTime() - beginFrameTime;
	}
}