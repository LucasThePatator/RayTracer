#pragma once

#include "commons.h"
#include "Ray.h"

class Light
{
public:
	Light(void);
	Light(Point3d &position, Color3d &color);
	~Light(void);

	Color3d computeColor(const Ray& ray, double dist);
	const Vector3d& getPosition() const;
	const Color3d& getColor() const;

private :
	Point3d position;
	Color3d color;
};

