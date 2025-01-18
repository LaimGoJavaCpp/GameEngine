#include "Camera.hpp"

Camera::Camera(glm::vec3 startPos)
{
	camPosition = startPos;
	view = glm::lookAt(
	glm::vec3{ 5.f, 0.f, 5.f },
	glm::vec3{ 0.f, 0.f, -1.f },
	glm::vec3{ 0.f, 1.f, 0.f }
	);
}

void Camera::lookAt(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3)
{
	view = glm::lookAt(
		pos1,
		pos2,
		pos3
	);
}