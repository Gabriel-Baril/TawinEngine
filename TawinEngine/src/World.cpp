#include "..\header\World.h"

World::World(std::vector<Shape>& shapes)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	GLuint totalBufferSize = 0;
	for (GLuint i = 0; i < shapes.size(); i++)
	{
		totalBufferSize += shapes.at(i).data.vertexBufferSize();
		totalBufferSize += shapes.at(i).data.indexBufferSize();
	} 
	glBufferData(GL_ARRAY_BUFFER, totalBufferSize, NULL, GL_STATIC_DRAW);
	GLuint currentOffSet = 0;
	for (GLuint i = 0; i < shapes.size();i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, currentOffSet, shapes.at(i).data.vertexBufferSize(), shapes.at(i).data.vertices);
		currentOffSet += shapes.at(i).data.vertexBufferSize();
		glBufferSubData(GL_ARRAY_BUFFER, currentOffSet, shapes.at(i).data.indexBufferSize(), shapes.at(i).data.indices);
		currentOffSet += shapes.at(i).data.indexBufferSize();
	}

	for (GLuint i = 0; i < shapes.size(); i++)
	{
		glGenVertexArrays(1, &shapes.at(i).vertexArrayObjectID);
	}
	std::cout << totalBufferSize << std::endl;
	currentOffSet = 0;
	for (GLuint i = 0; i < shapes.size();i++)
	{
		glBindVertexArray(shapes.at(i).vertexArrayObjectID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(currentOffSet));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(currentOffSet + sizeof(GLfloat) * 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(currentOffSet + sizeof(GLfloat) * 6));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);

		saveNumIndices.push_back(shapes.at(i).data.numIndices);
		currentOffSet += shapes.at(i).data.vertexBufferSize();
		saveIndexByteOffSet.push_back(currentOffSet);
		currentOffSet += shapes.at(i).data.indexBufferSize();
	}

	for (GLuint i = 0; i < shapes.size();i++)
	{
		shapes.at(i).data.cleanup();
	}
}

void World::render()
{
}

void World::update()
{

}
