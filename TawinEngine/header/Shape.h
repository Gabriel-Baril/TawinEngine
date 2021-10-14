#pragma once
#include "cpp_includes.h"
#include "opengl_includes.h"
#include "../header/ShapeData.h"
#include "../header/Vertex.h"
#include "../header/AABB.h"

class Shape
{
public:
	template <size_t numVertices, size_t numIndices>
	Shape(const vec3&, const vec3&, const vec3&, const vec3&, const float&, const float&, const float&, const vec3&, Vertex(&)[numVertices], GLushort(&)[numIndices]);
	Shape(const vec3&, const vec3&, const vec3&, const vec3&, const float&, const float&, const float&, const vec3&, const std::string path, bool isStatic);
	void update();

	static void split(const std::string& str, std::vector<std::string>& cont, const std::string& delims = " ")
	{
		std::size_t current, previous = 0;
		current = str.find_first_of(delims);
		while (current != std::string::npos) {
			cont.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find_first_of(delims, previous);
		}
		cont.push_back(str.substr(previous, current - previous));
	}

	mat4 getTranslationMatrix();
	mat4 getRotationMatrix();
	mat4 getScaleMatrix();
	mat4 getMatrixModel();
	bool getStatic();

	ShapeData data;
	GLuint vertexArrayObjectID;
	vec3 position;

	vec3 minPoint;
	vec3 maxPoint;

private:
	vec3 velocity;
	vec3 acceleration;

	vec3 rotationAxe;
	float rotationAngle;
	float rotationVelocity;
	float rotationAcceleration;
	vec3 scale;
	bool isStatic;
	mat4 staticMatrixModel;
};

template <size_t numVertices, size_t numIndices>
inline Shape::Shape(const vec3& position, const vec3& velocity, const vec3& acceleration,
	const vec3& rotationAxe, const float& rotationAngle, const float& rotationVelocity, const float& rotationAcceleration,
	const vec3& scale,
	Vertex(&dataVertices)[numVertices], GLushort(&dataIndices)[numIndices])
{
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->rotationAxe = rotationAxe;
	this->rotationAngle = rotationAngle;
	this->rotationVelocity = rotationVelocity;
	this->rotationAcceleration = rotationAcceleration;
	this->scale = scale;

	data.numVertices = numVertices;
	data.vertices = new Vertex[numVertices];
	memcpy(data.vertices, dataVertices, sizeof(dataVertices));

	data.numIndices = numIndices;
	data.indices = new GLushort[numIndices];
	memcpy(data.indices, dataIndices, sizeof(dataIndices));
}

inline Shape::Shape(const vec3& position, const vec3& velocity, const vec3& acceleration,
	const vec3& rotationAxe, const float& rotationAngle, const float& rotationVelocity, const float& rotationAcceleration,
	const vec3& scale,
	const std::string path, bool isStatic)
{
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->rotationAxe = rotationAxe;
	this->rotationAngle = rotationAngle;
	this->rotationVelocity = rotationVelocity;
	this->rotationAcceleration = rotationAcceleration;
	this->scale = scale;
	this->isStatic = isStatic;

	if (isStatic) 
		staticMatrixModel = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();

	// Crée un tableau contenant tout les strings (séparé par un espace)
	std::ifstream file(path);
	std::vector<std::string> dataFile;
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			Shape::split(line, dataFile, " ");
		}
	}
	bool passed = false;

	// stocke les strings dans leur tableau respectif (vertices ou indices)
	std::vector<GLfloat> vertices;
	std::vector<GLushort> indices;
	for (unsigned int i = 0; i < dataFile.size(); i++)
	{
		if (dataFile.at(i)._Equal("INDICES")) {
			passed = true;
			continue;
		}
		if (!passed) vertices.push_back(std::stof(dataFile.at(i)));
		if (passed) indices.push_back((GLushort)std::stof(dataFile.at(i)));
	}
	
	// normalise la couleur entre 0 et 1
	GLuint offSet = 0;
	for (GLuint i = 0;i < vertices.size();i++)
	{
		if (i != 0)
		{
			if (i % (6 + offSet) == 0 || i % (7 + offSet) == 0)
			{
				vertices.at(i) = (GLfloat)vertices.at(i) / (GLfloat)255;
			}
			if (i % (8 + offSet) == 0)
			{
				vertices.at(i) = (GLfloat)vertices.at(i) / (GLfloat)255;
				offSet += 9;
			}
		}
	}

	if (vertices.size() != 0)
	{
		minPoint.x = maxPoint.x = vertices.at(0);
		minPoint.y = maxPoint.y = vertices.at(1);
		minPoint.z = maxPoint.z = vertices.at(2);

		for (int i = 9; i < vertices.size(); i += 9)
		{
			if (vertices.at(i) < minPoint.x) minPoint.x = vertices.at(i);
			if (vertices.at(i + 1) < minPoint.y) minPoint.y = vertices.at(i + 1);
			if (vertices.at(i + 2) < minPoint.z) minPoint.z = vertices.at(i + 2);
			if (vertices.at(i) > maxPoint.x) minPoint.x = vertices.at(i);
			if (vertices.at(i + 1) > maxPoint.y) minPoint.y = vertices.at(i + 1);
			if (vertices.at(i + 2) > maxPoint.z) minPoint.z = vertices.at(i + 2);
		}
	}

	data.numVertices = vertices.size();
	data.vertices = new Vertex[data.numVertices];
	std::copy(vertices.begin(), vertices.end(), (GLfloat*)data.vertices);
	data.numIndices = indices.size();
	data.indices = new GLushort[data.numIndices];
	std::copy(indices.begin(), indices.end(), data.indices);
}