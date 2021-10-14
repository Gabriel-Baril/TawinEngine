#include "../header/Application.h"
#include "../header/Shader.h"

Camera Application::camera = Camera();

Application::Application(int const & width, int const & height, const char* title, std::vector<Shape>& shapes) : width(width), height(height), title(title), shapes(shapes)
{ }


int Application::init()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		system("PAUSE");
		return EXIT_FAILURE;
	}


	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(this->width, this->height, title, NULL, NULL);


	if (!Application::window)
	{
		std::cout << "FAILED TO CREATE WINDOW" << std::endl;
		system("PAUSE");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "FAILED TO INITIALIZE GLEW" << std::endl;
		system("PAUSE");
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDepthFunc(GL_LESS);

	world = World(shapes);

	return EXIT_SUCCESS;
}

Shader shader = Shader();

float fov = 10;
float angle = 0;


void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
		Application::camera.moveForward();
	if (key == GLFW_KEY_S)
		Application::camera.moveBackward();
	if (key == GLFW_KEY_D)
		Application::camera.moveRight();
	if (key == GLFW_KEY_A)
		Application::camera.moveLeft();
	if (key == GLFW_KEY_Q)
		Application::camera.moveUp();
	if (key == GLFW_KEY_E)
		Application::camera.moveDown();
}
void Application::update()
{
	shader.init("Shader/Vertex/shaderVertex.txt", "Shader/Fragment/shaderFragment.txt");
	shader.use();


	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPos(window, width / 2, height / 2);

	GLuint fullTransformationUniformLocation = glGetUniformLocation(shader.getProgram(), "fullTransformMatrix");
	std::vector<short> shapeIndex;
	glm::mat4 fullTransformMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 temp_viewproj;

	while (!glfwWindowShouldClose(Application::window))
	{
		Time.updateTime(GL_TRUE); // DO NOT TOUCH !!

		glfwGetFramebufferSize(Application::window, &this->width, &this->height);
		glViewport(0, 0, this->width, this->height);
		glfwGetCursorPos(this->window, &this->mouse.x, &this->mouse.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (mouse.x > 0 && mouse.x < width && mouse.y > 0 && mouse.y < height) {
			Application::camera.mouseUpdate(mouse);
		}

		float t_x = 2 * (float)mouse.x / (float)width - 1;
		//float t_y = 2 * (float)mouse.y / (float)height - 1;
		//std::cout << "(" << t_x << "," << t_y << ")" << std::endl;


		shapeIndex = std::vector<short>();
		for (GLuint i = 0; i < shapes.size(); i++)
		{
			if (glm::distance(Application::camera.position, shapes.at(i).position) < 100)
			{
				shapeIndex.push_back(i);
			}
		}

		if (shapeIndex.size() != 0)
		{
			projectionMatrix = glm::perspective(2.0f, ((float)this->width) / this->height, 0.1f, 100.0f);
			viewMatrix = Application::camera.getWorldToViewMatrix();
			temp_viewproj = projectionMatrix * viewMatrix;

			for (GLuint i = 0; i < shapeIndex.size(); i++)
			{
				if (!shapes.at(shapeIndex.at(i)).getStatic())
					shapes.at(shapeIndex.at(i)).update();
				glBindVertexArray(shapes.at(shapeIndex.at(i)).vertexArrayObjectID);
				fullTransformMatrix = temp_viewproj * shapes.at(shapeIndex.at(i)).getMatrixModel();
				glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
				glDrawElements(GL_TRIANGLES, world.saveNumIndices.at(shapeIndex.at(i)), GL_UNSIGNED_SHORT, (void*)world.saveIndexByteOffSet.at(shapeIndex.at(i)));
			}
		}

		glfwSwapBuffers(window); // Swap front and back buffers
		glfwPollEvents(); // Poll for and process events
		Time.delta_time = (glfwGetTime() - Time.currentTime) * 1000; // DO NOT TOUCH !!
	}
}

void Application::cleanup()
{
	shader.free();
	for (GLuint i = 0; i < shapes.size(); i++)
	{
		glDeleteVertexArrays(1, &shapes.at(i).vertexArrayObjectID);
	}
	glDeleteBuffers(1, &world.bufferID);
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

