#pragma once

#include "commons.h"
#include "Ray.h"

typedef struct
{
	/// Normale de la primitive en un point
	Vector3d normal;
	/// Couleur du point
	Color3d color;
	/// "Couleur" de la réflexion
	Color3d reflect;

} MaterialPoint;

class Primitive
{
public:
	Primitive(void) {};
	virtual ~Primitive(void) {};

	virtual bool intersect(const Ray &ray, double &dist) = 0;

	virtual bool computeColorNormal(const Ray& ray, double dist, MaterialPoint &caracteristics) = 0;

	virtual bool setColor(Color3d &color) = 0;
};



