#include "StdAfx.h"
#include "Sphere.h"

#include <cmath>

Sphere::Sphere(void)
{
}

Sphere::Sphere(const Point3d &center, double radius) 
	:center(center), radius(radius)
{
	
}

Sphere::~Sphere(void)
{
}

bool Sphere::intersect(const Ray &ray, double &dist) {
	double a = norm2_2(ray.getDirection());
	double b = (ray.getOrigin() - center) * ray.getDirection();
	double c = norm2_2(ray.getOrigin() - center) - (radius*radius);

	double delta = b * b - a*c;

	if (delta < 0.f)
		return false;

	double x1 = (- b - sqrt(delta))/a;
	double x2 = (- b + sqrt(delta))/a;

	dist  = (x1 < x2 ? x1 : x2) / norm2(ray.getDirection());

	return true;
}

bool Sphere::computeColorNormal(const Ray& ray, double dist, MaterialPoint &caracteristics) {
	Point3d intersectionPoint = ray.getOrigin() + (dist * ray.getDirection());

	//Calcul de la normale
	caracteristics.normal = intersectionPoint - center;
	caracteristics.normal = caracteristics.normal/norm2(caracteristics.normal);

	caracteristics.color = this->color;
	caracteristics.reflect = 0.7;

	caracteristics.refractIndex = 1.5;
	caracteristics.refractAbs = 1;

	return true;
}

bool Sphere::setColor(Color3d &color) {
	this->color = color;
	return true;
}

bool Sphere::setMaterial(const Material &material) 
{
	this->material = material;
	return true;
}

