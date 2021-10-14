#pragma once
#include "cpp_includes.h"
#include "opengl_includes.h"
#include "../header/AABB.h"

class Camera {
public:
	Camera();
	glm::mat4 getWorldToViewMatrix() const;
	glm::vec2 oldMousePosition;


	glm::vec3 getPerpViewAndUp();
	void mouseUpdate(const glm::vec2& mouse);

	void moveRight();
	void moveLeft();
	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();

	glm::vec3 position;
private:
	glm::vec3 viewDirection;
	const glm::vec3 UP;
};