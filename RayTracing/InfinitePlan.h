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

	int intersect(const Ray &ray, double &dist);
	bool getPoint(const Ray& ray, double dist, MaterialPoint &caracteristics);

private :

	Point3d point;
	Color3d color;
	Vector3d normal;
};

