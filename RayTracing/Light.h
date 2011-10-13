#pragma once

#include "commons.h"
#include "Ray.h"
#include "Primitive.h"

class Light
{
public:
	Light(void);
	Light(Primitive &primitive, Material &Material);
	~Light(void);

	Color3d computeColor(const Ray& ray, double dist);
	bool isPunctual() const {return punctual;}

	const Primitive& getPrimitive() {return *primitive;}
	const Vector3d& getPosition() const;
	const Color3d& getColor() const {return color;}

private :

	Point3d position;
	Color3d color;
	Primitive *primitive;
	bool punctual;
};

