#include "StdAfx.h"
#include "SimpleScene.h"

#include <algorithm>
#include <cmath>

SimpleScene::SimpleScene(void)
{
}


SimpleScene::~SimpleScene(void) {
	//for(std::vector<Primitive*>::const_iterator it = primitives.begin(); it != primitives.end(); ++it)
      //delete *it;
}

bool SimpleScene::addPrimitive(Primitive &primitive) {
	if(std::find(primitives.begin(), primitives.end(), &primitive) != primitives.end())
      return false;

	primitives.push_back(&primitive);
	return true;
}

Primitive * SimpleScene::removePrimitive(int index) {
	std::vector<Primitive*>::iterator it = primitives.begin();
    std::advance(it, index);
    Primitive* primitive = *it;
    primitives.erase(it);
    return primitive;
}

Primitive * SimpleScene::getPrimitive(int index) {
	std::vector<Primitive*>::iterator it = primitives.begin();
    std::advance(it, index);
    Primitive* primitive = *it;
    return primitive;
}

int SimpleScene::getNbPrimitives() 
{
	return primitives.size();
}

int SimpleScene::getNbLights() 
{
	return lights.size();
}

Light * SimpleScene::getLight(int index)
{
	std::vector<Light*>::iterator it = lights.begin();
    std::advance(it, index);
    Light* light = *it;
    return light;
}


bool SimpleScene::addLight(Light &light) {
	if(std::find(lights.begin(), lights.end(), &light) != lights.end())
      return false;

	lights.push_back(&light);
	return true;
}

Light * SimpleScene::removeLight(int index) {
	std::vector<Light*>::iterator it = lights.begin();
    std::advance(it, index);
    Light* light = *it;
    lights.erase(it);
    return light;
}



