#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(glm::vec3 startPos);
	glm::mat4 getView() { return view; }
	glm::vec3 getCamPosition() { return camPosition; }
	void setPosition(glm::vec3 pos) { camPosition = pos; }
	void setViev(glm::mat4 newView) { view = newView; }
	void lookAt(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3);
private:
	glm::mat4 view;
	glm::vec3 camPosition;
};