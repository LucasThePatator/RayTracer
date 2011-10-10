#include "StdAfx.h"
#include "Ray.h"


Ray::Ray(void)
{
	origin = Point3d(0);
}

Ray::Ray(Point3d origin, Vector3d direction) {
	for(int i = 0; i < 3; i++) {
		this->origin = origin;
		this->direction = direction;
	}
}


Ray::~Ray(void)
{
}
