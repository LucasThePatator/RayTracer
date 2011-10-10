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

int SimpleScene::getFirstCollision(const Ray& ray, double& dist)
{
	double min_dist = std::numeric_limits<double>::max();
	long min_primitive = -1;

	for(std::vector<Primitive*>::const_iterator it = primitives.begin(); it != primitives.end(); ++it)
	{
		double dist;
		bool test = (*it)->intersect(ray, dist);

		if(test && (dist > 0.01f) && (dist < min_dist))
		{
			min_primitive = it - primitives.begin();
			min_dist = dist;
		}
	}


	if(min_primitive == -1)
		return -1;
	else
	{
		dist = min_dist;
		return min_primitive;
	}
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

bool SimpleScene::testCollision(const Ray& ray, double dist)
{
	for(std::vector<Primitive*>::const_iterator it = primitives.begin(); it != primitives.end(); ++it)
	{
		double t_dist;
		bool test = (*it)->intersect(ray, t_dist);

		if(test && (0.01f < t_dist) && (t_dist < dist))
		{
			return true;
		}
	}
	return false;
}

Color3d SimpleScene::computeColor(Point3d point, MaterialPoint caracteristics) {
	
	Color3d color(0);
	//Pour toutes les lumières
	for(std::vector<Light*>::const_iterator it = lights.begin(); it != lights.end(); it++) {
		Light *light = *it;
		//Calcul du produit scalaire entre le chemin de la lumière et la normale
		Vector3d path = light->getPosition() - point;
		double pathSize = norm2(path);
		path = path/norm2(path);
		Ray ray(point, path);

		//Pas de modification de la couleur si un objet est entre la lumière et le point
		if(testCollision(ray, pathSize))
			continue;


		/* Gestion de la reflexion */
		//sinon on calcul le produit scalaire entre la normale au point et le chemin
		double cosphi = path * caracteristics.normal;
		double spec = 1 * pow(cosphi, 20);
		if (cosphi < 0) //On est dans le mauvais sens
			continue;
		
		//Sinon on ajoute a la couleur la couleur de la source lumineuse en fonction du produit scalaire
		
		Color3d t_color =  (1 + spec) * cosphi * dot(light->getColor(),caracteristics.color);
		color = t_color + color;

		/* Gestion de la refraction */

	}

	return color;
}

