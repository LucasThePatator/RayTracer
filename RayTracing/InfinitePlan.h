#pragma once
#include "primitive.h"
#include "commons.h"

class InfinitePlan :
	public Primitive
{


public:
	InfinitePlan(void);
	InfinitePlan(const Vector3d &normal, const Point3d &Point);
	~InfinitePlan(void);

	bool intersect(const Ray &ray, double &dist);
	bool computeColorNormal(const Ray& ray, double dist, MaterialPoint &caracteristics);
	bool setColor(Color3d &color);
	bool setMaterial(const Material &material);

private :

	Point3d point;
	Color3d color;
	Vector3d normal;
	Material material;
	
};

