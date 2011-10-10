#pragma once

#include "Primitive.h"
#include <vector>

#include "Light.h"

class SimpleScene
{
public:
	SimpleScene(void);
	~SimpleScene(void);

	bool addPrimitive(Primitive &primitive);
	Primitive * removePrimitive(int index);
	Primitive * getPrimitive(int index);

	bool addLight(Light &primitive);
	Light * removeLight(int index);

	int getFirstCollision(const Ray& ray, double& dist);
	bool testCollision(const Ray& ray, double dist);
	Color3d computeColor(Point3d point, MaterialPoint caracteristics);

private :

	std::vector<Primitive*> primitives;
	std::vector<Light*> lights;
};

