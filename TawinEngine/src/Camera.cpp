#include "..\header\Camera.h"

Camera::Camera() : 
	viewDirection(0.0f,0.0f,-1.0f),
	UP(0.0f,1.0f,0.0f)
{
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection,UP);
}

glm::vec3 Camera::getPerpViewAndUp()
{
	return glm::cross(viewDirection, UP);
}

void Camera::mouseUpdate(const glm::vec2 & currentMousePosition)
{
	glm::vec2 mouseDelta = currentMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f) {
		oldMousePosition = currentMousePosition;
		return;
	}
	const float ROTATIONAL_SPEED = 0.004;
	viewDirection = glm::mat3(glm::rotate(mouseDelta.x * ROTATIONAL_SPEED, UP) * glm::rotate(mouseDelta.y * ROTATIONAL_SPEED, getPerpViewAndUp() ) ) * viewDirection;

	oldMousePosition = currentMousePosition;
}

void Camera::moveRight()
{
	position += getPerpViewAndUp();
}

void Camera::moveLeft()
{
	position -= getPerpViewAndUp();
}

void Camera::moveForward()
{
	position += viewDirection;
}

void Camera::moveBackward()
{
	position -= viewDirection;
}

void Camera::moveUp()
{
	position += UP;
}

void Camera::moveDown()
{
	position -= UP;
}
