#pragma once
#include "cpp_includes.h"
#include "opengl_includes.h"


class AABB
{
public:
	//AABB();
	AABB(vec3 p1, vec3 p2);
	AABB(vec3 p, float width, float height, float depth);

	static bool AABB_AABB_COLLIDE(AABB b1,AABB b2)
	{
		return b2.startPoint.x + b2.width > b1.startPoint.x && b2.startPoint.x < b1.startPoint.x + b1.width &&
			b2.startPoint.y + b2.height > b1.startPoint.y && b2.startPoint.y < b1.startPoint.y + b1.height &&
			b2.startPoint.z + b2.depth > b1.startPoint.z && b2.startPoint.z < b1.startPoint.z + b1.depth;
	}


private:
	vec3 startPoint;
	vec3 endPoint;
	float width;
	float height;
	float depth;
};