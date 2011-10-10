#include "StdAfx.h"
#include "RayTracer.h"
#include "Primitive.h"

RayTracer::RayTracer(double pixelWidth, double pixelHeight, int width, int height, double focale)
	:origin(0.), direction(1.), pixelWidth(pixelWidth), pixelHeight(pixelHeight), width(width), height(height), focale(focale)
{
}


RayTracer::~RayTracer(void)
{
}

void draw(double* screen) {
}

void RayTracer::generateRay(int i, int j, Ray& ray) const
{
	//For the time being, the camera is on the x axis... we'll see later if we want to do something fancier.

	ray.getOrigin()[0] = 0;
	ray.getOrigin()[1] = 0;
	ray.getOrigin()[2] = 0;
	
	ray.getDirection()[0] = +focale;
	ray.getDirection()[1] = pixelWidth * (i - (width / 2));
	ray.getDirection()[2] = - pixelHeight * (j - (height / 2));

	ray.getDirection() = ray.getDirection()/norm2(ray.getDirection());
}

void RayTracer::setViewer(double pixelWidth, double pixelHeight, const Vector3d& origin, const Vector3d& direction)
{
	this->pixelHeight = pixelHeight;
	this->pixelWidth = pixelWidth;
	this->origin = origin;
	this->direction = direction;
}

void RayTracer::setScene(SimpleScene *scene) 
{
	this->scene = scene;
}

void RayTracer::setResolution(int width, int height) 
{
	this->width;
	this->height;
}

void RayTracer::draw(Color3d* screen) const {

	Ray ray(origin, direction);
	
	for(int i = 0; i < width; i++) 
	{
		for(int j = 0; j < height; j++) 
		{
			Color3d color(0.f);
			double dist;
			generateRay(i, j, ray);

			computeColor(ray, color, 0);

			screen[i + width*j] = color;
		}
	}
}

void RayTracer::computeColor(const Ray& ray, Color3d& color, unsigned int level) const
{
	double dist;
	int index = scene->getFirstCollision(ray, dist);
	if(index < 0)
		return;

	Primitive* primitive = scene->getPrimitive(index);
	MaterialPoint caracteristics;

	//Calcul de la couleur due a la lumière et au reflet
	Color3d nulColor(0);
	primitive->computeColorNormal(ray, dist, caracteristics); //On récupère la couleur et les caractéristiques au point
	color = scene->computeColor(ray.getOrigin() + dist * ray.getDirection(), caracteristics);

	int levels = 10;

	if(level < levels)
	{
	
		/*calcul du rayon reflechi*/
		Ray ray_refl(ray.getOrigin() + dist * ray.getDirection(), ray.getDirection() - (ray.getDirection() * caracteristics.normal) * 2 * caracteristics.normal);
		ray_refl.getDirection() = ray_refl.getDirection()/norm2(ray_refl.getDirection());

		Color3d color_refl(0.);
		computeColor(ray_refl, color_refl, level+1); //Calcul du rayon reflechi

		color = color + dot(color_refl, caracteristics.reflect);

		/*gestion de la refraction*/
		if (caracteristics.refractAbs > 0) {
			Vector3d i = ray.getDirection()/norm2(ray.getDirection());
			double refr = (1.0f)/(caracteristics.refractIndex);
			double cos1 = caracteristics.normal * (-i);
			if (cos1 < 0) 
			{
				caracteristics.normal = - caracteristics.normal;
				cos1 = -cos1;
				//refr = 1/refr;
			}

			double cos2 = 1 - refr*refr*(1-cos1*cos1);
			if (cos2 > 0) {
				cos2 = sqrt(cos2);
				Vector3d v = refr * i + (refr*cos1 - cos2)*caracteristics.normal;

				Ray ray_refr(ray.getOrigin() + dist * ray.getDirection(), v);
				ray_refr.getDirection() = ray_refr.getDirection()/norm2(ray_refr.getDirection());

				Color3d color_refr(0.);
				computeColor(ray_refr, color_refr, level+1); //calcul du rayon refracté

				color = color + caracteristics.refractAbs * color_refr ;
			}
		}
	}
}

