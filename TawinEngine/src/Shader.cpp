#include "../header/Shader.h"

Shader::Shader()
{
}

void Shader::init(const std::string vertexPath, const std::string fragmentPath)
{
	std::string vertexShaderData_s = Shader::readShaderFile(vertexPath, "ERROR IN SHADER::READ::VERTEX (Could not open file)");
	std::string fragmentShaderData_s = Shader::readShaderFile(fragmentPath, "ERROR IN SHADER::READ::FRAGMENT (Could not open file)");

	const char* vertexShaderData = vertexShaderData_s.c_str();
	const char* fragmentShaderData = fragmentShaderData_s.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderData, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLint length;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetShaderInfoLog(vertexShader, length, &length, info);

		std::cout << "ERROR IN SHADER::VERTEX::COMPILE" << std::endl;
		std::cout << info << std::endl;

		glfwTerminate();
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderData, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetShaderInfoLog(fragmentShader, length, &length, info);

		std::cout << "ERROR IN SHADER::FRAGMENT::COMPILE" << std::endl;
		std::cout << info << std::endl;

		glfwTerminate();
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetProgramInfoLog(program, length, &length, info);

		std::cout << "ERROR IN SHADER::LINKING" << std::endl;
		std::cout << info << std::endl;

		glfwTerminate();
	}

	this->program = program;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_DELETE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetShaderInfoLog(vertexShader, length, &length, info);

		std::cout << "ERROR ON SHADER::VERTEX::DELETE" << std::endl;
		std::cout << info << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_DELETE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetShaderInfoLog(fragmentShader, length, &length, info);

		std::cout << "ERROR ON SHADER::FRAGMENT::DELETE" << std::endl;
		std::cout << info << std::endl;
	}

}

void Shader::use()
{
	glUseProgram(this->program);
}

void Shader::free()
{
	glUseProgram(0);
	glDeleteProgram(this->program);
}

GLuint Shader::getProgram()
{
	return this->program;
}

std::string Shader::readShaderFile(const std::string path, const char * error)
{
	std::ifstream file(path);
	std::string data;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			data += line + '\n';
		}
	}
	else
	{
		std::cout << error << std::endl;
	}
	file.close();
	return data;
}