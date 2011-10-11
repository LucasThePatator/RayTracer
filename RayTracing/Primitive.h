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
	/// "Couleur" de la réflexion
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

	virtual int intersect(const Ray &ray, double &dist) = 0;

	virtual bool getPoint(const Ray& ray, double dist, MaterialPoint &caracteristics) = 0;

	virtual bool setColor(Color3d &color) = 0;

	void setMaterial(const Material &material) {this->material = material;};
	const Material &getMaterial() const {return material;}

private :
	Material material;
};



