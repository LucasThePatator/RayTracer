#pragma once

#include "commons.h"
#include "Ray.h"

#include "Material.h"

typedef struct
{
	/// Normale de la primitive en un point
	Vector3d normal;
	/// Couleur du point
	Color3d color;
	/// "Couleur" de la r�flexion
	Color3d reflect;
	/// Indice(s) de refraction
	double refractIndex;
	/// Indice(s) d'absorption pour la refraction
	double refractAbs;

} MaterialPoint;

class Primitive
{
public:
	Primitive(void) {};
	virtual ~Primitive(void) {};

	virtual bool intersect(const Ray &ray, double &dist) = 0;

	virtual bool computeColorNormal(const Ray& ray, double dist, MaterialPoint &caracteristics) = 0;

	virtual bool setColor(Color3d &color) = 0;

	virtual bool setMaterial(const Material &material) = 0;
};



