#include "StdAfx.h"
#include "InfinitePlan.h"

InfinitePlan::InfinitePlan(void)
{

}

InfinitePlan::InfinitePlan(const Vector3d &normal, const Point3d &point) 
	:normal(normal), point(point)
{

}


InfinitePlan::~InfinitePlan(void)
{
	
}

bool InfinitePlan::intersect(const Ray &ray, double &dist) 
{
	if (ray.getDirection() * normal == 0)
		return false;

	Point3d origin = ray.getOrigin();
	dist = -((origin - point) * normal) / (ray.getDirection() * normal);
	if (dist > 0)
		return true;

	return false;
}

bool InfinitePlan::computeColorNormal(const Ray& ray, double dist, MaterialPoint &caracteristics) {
	caracteristics.color = color;
	caracteristics.normal = normal / norm2(normal);
	caracteristics.reflect = 1;
	return true;
}

bool InfinitePlan::setColor(Color3d &color) 
{
	this->color = color;
	return true;
}
