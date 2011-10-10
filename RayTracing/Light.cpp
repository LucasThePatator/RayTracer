#include "StdAfx.h"
#include "Light.h"


Light::Light(void)
{
}

Light::Light(Point3d &position, Color3d &color)
: position(position), color(color)
{	
}

Light::~Light(void)
{
}

Color3d Light::computeColor(const Ray& ray, double dist)
{
	return (1. / (dist * dist))*color;
}

const Vector3d& Light::getPosition() const
{
	return position;
}

const Color3d& Light::getColor() const 
{
	return color;
}
