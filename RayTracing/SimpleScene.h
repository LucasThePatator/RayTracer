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

	int getNbPrimitives();

	bool addLight(Light &primitive);
	Light * removeLight(int index);
	Light * getLight(int index);

	int getNbLights();

private :

	std::vector<Primitive*> primitives;
	std::vector<Light*> lights;
};

