#pragma once
#include "cpp_includes.h"
#include "opengl_includes.h"

class Shader {
public:
	Shader();

	void init(const std::string vertexPath, const std::string fragmentPath);
	void use();
	void free();
	GLuint getProgram();

	static std::string readShaderFile(const std::string path, const char * error);
private:
	GLuint program;
};