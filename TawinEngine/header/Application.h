#pragma once
#include "cpp_includes.h"
#include "opengl_includes.h"
#include "../header/Camera.h"
#include "../header/World.h"

using glm::vec3;

class Application {
private:
	struct TimeData {
		long totalFPS = 0;
		long currentFPS = 0;
		double lastTime = glfwGetTime();
		double currentTime = 0;
		long lastFPS = 0;
		double ms_per_frame = 0;
		double delta_time = 0;
		long getDifferential() { return currentFPS - lastFPS; }
		void updateTime(GLboolean showData) {
			currentTime = glfwGetTime();
			currentFPS++;
			if (currentTime - lastTime >= 1.0) {
				ms_per_frame = 1000.0 / double(currentFPS);
				totalFPS += currentFPS;
				if (showData) {
					std::cout << "[" << (int)currentTime << " SECONDS] "
							  << "[" << ms_per_frame << " MS/FRAME] " 
							  << "[" << currentFPS << " FPS] "
							  << "[" << getDifferential() << " DIFFERENTIAL] "
						      << "[" << totalFPS << " TOTAL FRAMES] "
						      << "[" << delta_time << " DELTA TIME]" << std::endl;
				}
				lastFPS = currentFPS;
				currentFPS = 0;
				lastTime += 1.0;
			}
		}
	} Time;
	GLFWwindow* window;
	GLint width;
	GLint height;
	const char* title;
	std::vector<Shape>& shapes;
	World world;
	glm::highp_dvec2 mouse = glm::highp_dvec2(0.0,0.0);
public:
	static Camera camera;
	Application(int const& width,int const& height, const char* title, std::vector<Shape>& shapes);

	int init();
	void update();
	void cleanup();
	friend void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
};

