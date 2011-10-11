#pragma once
#include "primitive.h"
#include "commons.h"

class Sphere :
	public Primitive
{
public:
	Sphere(void);
	Sphere(const Point3d &center, double radius);
	~Sphere(void);

	int intersect(const Ray &ray, double &dist);
	bool getPoint(const Ray& ray, double dist, MaterialPoint &caracteristics);
	bool setColor(Color3d &color);
	bool setMaterial(const Material &material);

private :
	Color3d color;
	Point3d center;
	double radius;
	Material material;
};

