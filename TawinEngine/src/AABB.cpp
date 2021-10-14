#include "..\header\AABB.h"

AABB::AABB(vec3 p1, vec3 p2)
{
	this->startPoint = p1;
	this->endPoint = p2;
	this->width = abs(p2.x - p1.x);
	this->height = abs(p2.y - p1.y);
	this->depth = abs(p2.z - p1.z);
}

AABB::AABB(vec3 p, float width, float height, float depth)
{
	this->startPoint = p;
	this->width = width;
	this->height = height;
	this->depth = depth;
}
