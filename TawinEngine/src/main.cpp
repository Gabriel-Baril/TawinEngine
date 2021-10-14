#pragma once
#include "../header/cpp_includes.h"
#include "../header/opengl_includes.h"
#include "../header/Application.h"
#include "../header/Camera.h"
#include "../header/Shape.h"
#include "../header/World.h"

#define PI 3.1415

void printVec3(vec3 v)
{
	printf("(%f,%f,%f)",v.x,v.y,v.z);
	std::cout << std::endl;
}

int main(void)
{
	std::vector<Shape> shapes;
	
	for (int i = -2; i < 2;i++) {
		for (int j = -2; j < 2; j++) {
			shapes.emplace_back(vec3(i + i*2, sqrt((i + j)*sin(i*j)), j + j*2), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1, 0, 0), 0, 0.001, 0, vec3(1, 1, 1), "D:/_DEV/_PROJECTS/CPP/TawinEngine/BLENDER/cat.ply", false);
		}
	}
	
	
	//shapes.push_back(Shape(vec3(0.0f, -5.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1, 0, 0), -PI/2, 0, 0, vec3(1, 1, 1), "D:/_PROGRAMMING/OpenGL_project/TawinEngine/BLENDER/table.ply", true));
	//shapes.push_back(Shape(vec3(0.0f, -5.0f, 0), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1, 0, 0), -PI/2, 0, 0, vec3(1, 1, 1), "D:/_PROGRAMMING/OpenGL_project/TawinEngine/BLENDER/table.ply", true));
	//shapes.push_back(Shape(vec3(10.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0, 1, 0), -PI/2, 0.001, 0, vec3(2, 2, 2), "D:/_PROGRAMMING/OpenGL_project/TawinEngine/BLENDER/cat.ply", false));
	//shapes.push_back(Shape(vec3(0.0f, 6.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0, 1, 0), 0, 0.0f , 0, vec3(1, 1, 1), "D:/_PROGRAMMING/OpenGL_project/TawinEngine/BLENDER/testCube.ply",true));
	//shapes.push_back(Shape(vec3(0.0f, -10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1, 0, 0), PI/2, 0, 0, vec3(10, 10, 2), "D:/_PROGRAMMING/OpenGL_project/TawinEngine/BLENDER/planeColor.ply",true));

	Application engine(800,600,"TawinEngine",shapes);
	engine.init();
	engine.update();
	engine.cleanup();
	
	return EXIT_SUCCESS;
}