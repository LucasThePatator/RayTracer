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

int Sphere::intersect(const Ray &ray, double &dist) {
	double a = norm2_2(ray.getDirection());
	double b = (ray.getOrigin() - center) * ray.getDirection();
	double c = norm2_2(ray.getOrigin() - center) - (radius*radius);

	double delta = b * b - a*c;

	if (delta < 0.f)
		return 0;

	double x1 = (- b - sqrt(delta))/a;
	double x2 = (- b + sqrt(delta))/a;

	//Si les deux sont négatifs, la sphère est derrière et le rayon ne touche donc pas.
	if ((x1 < 0) && (x2 < 0))
		return 0;

	//dans le cas ou l'un des deux est négatif, c'est que le rayon est parti de l'intérieur de la sphère, on prend toujours le plus petit positif
	if (x1 < 0) {
		dist = x2;
		return -1;
		
	}

	if (x2 < 0) {
		dist = x1;
		return -1;
		
	}

	//Si les deux sont positifs
	dist  = (x1 < x2 ? x1 : x2);
	return 1;
}

bool Sphere::getPoint(const Ray& ray, double dist, MaterialPoint &caracteristics) {
	Point3d intersectionPoint = ray.getOrigin() + (dist * ray.getDirection());

	//Calcul de la normale
	caracteristics.normal = intersectionPoint - center;
	caracteristics.normal = caracteristics.normal/norm2(caracteristics.normal);

	caracteristics.color = this->color;
	caracteristics.reflect = 1;

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

