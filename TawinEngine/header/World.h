#pragma once
#include "cpp_includes.h"
#include "opengl_includes.h"
#include "Shape.h"

class World {
public:
	World() {}
	World(std::vector<Shape>&);
	void render();
	void update();

	std::vector<GLuint> saveNumIndices = std::vector<GLuint>();
	std::vector<GLuint> saveIndexByteOffSet = std::vector<GLuint>();
	GLuint bufferID = 0;
private:
};