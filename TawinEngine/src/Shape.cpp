#include "..\header\Shape.h"

mat4 Shape::getMatrixModel()
{
	if (this->isStatic)
		return this->staticMatrixModel;
	return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

bool Shape::getStatic()
{
	return this->isStatic;
}

void Shape::update()
{
	position += velocity;
	velocity += acceleration;
	rotationAngle += rotationVelocity;
	rotationVelocity += rotationAcceleration;
}

mat4 Shape::getTranslationMatrix()
{
	return glm::translate(position);
}

mat4 Shape::getRotationMatrix()
{
	return glm::rotate(rotationAngle, rotationAxe);
}

mat4 Shape::getScaleMatrix()
{
	return glm::scale(scale);
}
