#pragma once

#include "commons.h"

class Ray
{
public:
	Ray(void);
	Ray(Point3d origin, Vector3d direction);
	~Ray(void);

	Point3d &getOrigin() {
		return origin;
	}

	const Point3d &getOrigin() const {
		return origin;
	}

	Vector3d &getDirection () {
		return direction;
	}

	const Vector3d &getDirection () const {
		return direction;
	}
	

private :
	Point3d origin;
	Vector3d direction;

};

