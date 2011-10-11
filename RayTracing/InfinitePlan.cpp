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

int InfinitePlan::intersect(const Ray &ray, double &dist) 
{
	double scal = ray.getDirection() * normal;
	if (scal == 0)
		return false;

	Point3d origin = ray.getOrigin();
	dist = -((origin - point) * normal) / (ray.getDirection() * normal);

	if (dist > 0) 
	{
		return scal > 0 ? -1 : 1;
	}

	return 0;
}

bool InfinitePlan::getPoint(const Ray& ray, double dist, MaterialPoint &caracteristics) {
	caracteristics.color = color;
	caracteristics.normal = normal / norm2(normal);
	caracteristics.reflect = 0.7;

	caracteristics.refractIndex = 1;
	caracteristics.refractAbs = 0;

	return true;
}

bool InfinitePlan::setColor(Color3d &color) 
{
	this->color = color;
	return true;
}

bool InfinitePlan::setMaterial(const Material &material) 
{
	this->material = material;
	return true;
}
