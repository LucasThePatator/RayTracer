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

void RayTracer::generateRay(double i, double j, Ray& ray) const
{
	//For the time being, the camera is on the x axis... we'll see later if we want to do something fancier.

	ray.getOrigin()[0] = 0;
	ray.getOrigin()[1] = 0;
	ray.getOrigin()[2] = 0;

	ray.getDirection()[0] = +focale;
	ray.getDirection()[1] = pixelWidth * (i - (double)(width / 2));
	ray.getDirection()[2] = - pixelHeight * (j - (double)(height / 2));

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

			//superSampling
			for(int k = 0; k < 4; k++) 
			{
				for (int l = 0; l < 4; l++)
				{

					generateRay(i + k/4.0, j + l/4.0, ray);

					RayTrace(ray, color, 0);

					screen[i + width*j] = screen[i + width*j]+ color/16.0;
				}
			}
		}
	}
}

void RayTracer::RayTrace(const Ray& ray, Color3d& color, unsigned int level) const
{
	Color3d black(0);
	color = black;

	//Recherche de la première collision
	double dist = LARGE_DOUBLE; //initialisation a une valeur très élevée
	int interResult = 0;
	Primitive *primitive;
	for(int i = 0; i < scene->getNbPrimitives(); i++)
	{
		Primitive *tempPrim = scene->getPrimitive(i);
		double tempDist = 0;
		int res = tempPrim->intersect(ray, tempDist);
		if(res) 
		{
			if(tempDist <= dist && tempDist > EPSILON) {
				primitive = tempPrim;
				interResult = res;
				dist = tempDist;
			}
		}
	}

	//Si il n'y a aucune collision
	if(interResult == 0) {
		color = Color3d(0);
		return;
	}

	MaterialPoint caracteristics;

	//Calcul de la couleur due a la lumière et au reflet
	primitive->getPoint(ray, dist, caracteristics); //On récupère la couleur et les caractéristiques au point (normale, indice, etc...)
	Point3d point = ray.getOrigin() + dist * ray.getDirection(); //Point d'intersection

	/* Gestion de l'éclairage */

	double BLFactor = 1;
	//Pour toutes les lumières
	if (interResult == 1) //Si l'on sort d'une primitive, il n'y pas de diffusion
	{
		for(int i = 0; i < scene->getNbLights(); i++) {

			Light *light = scene->getLight(i);
			//Calcul du produit scalaire entre le chemin de la lumière et la normale
			Vector3d path = light->getPosition() - point;
			double pathSize = norm2(path);
			path = path/norm2(path);
			Ray ray(point, path);

			//Pas de modification de la couleur si un objet est entre la lumière et le point

			bool visibleLight = true;
			for(int j = 0; j < scene->getNbPrimitives(); j ++)
			{
				double t_dist;
				bool test = (scene->getPrimitive(j)->intersect(ray, t_dist)) == 1;

				if(test && (EPSILON < t_dist) && (t_dist < pathSize - EPSILON))
				{
					visibleLight = false;
					break;
				}
			}

			//sinon on calcul le produit scalaire entre la normale au point et le chemin
			double cosphi = path * caracteristics.normal;
			double spec = 1 * pow(cosphi, 20);

			//Sinon on ajoute a la couleur la couleur de la source lumineuse en fonction du produit scalaire
			if (visibleLight && (cosphi >= 0)) 
			{
				Color3d t_color = (1+spec) * cosphi * dot(light->getColor(), caracteristics.color);
				color = caracteristics.diffusion * t_color + color;
			}
		}
	} else //Si on tape à l'intérieur d'une primitive, c'est que l'on va sortir de celle-ci => Loi de B-L
	{
		BLFactor = exp( - caracteristics.refractAbs * dist);
	}
	unsigned int levels = 10; //niveau de reflexion;

	if(level < levels)
	{

		/*calcul du rayon reflechi*/
		if (interResult == 1) {
			Ray ray_refl(point - EPSILON * ray.getDirection(), ray.getDirection() - ((double)interResult * ray.getDirection() * caracteristics.normal) * 2 * interResult*caracteristics.normal);
			ray_refl.getDirection() = ray_refl.getDirection()/norm2(ray_refl.getDirection());

			Color3d color_refl(0.);
			RayTrace(ray_refl, color_refl, level+1); //Calcul du rayon reflechi

			color = color + dot(caracteristics.reflect, color_refl);
		}

		///*gestion de la refraction*/
		if (caracteristics.refractAbs < LARGE_DOUBLE) {

			Vector3d i = ray.getDirection()/norm2(ray.getDirection());
			double refr = (1.0f)/(caracteristics.refractIndex);

			if (interResult == -1)
				refr = 1/refr;

			Vector3d N = ((double)interResult) * caracteristics.normal ;
			double cos1 = -N * i;

			double cos2 = 1 - refr*refr*(1-cos1*cos1);
			if (cos2 > 0) {
				cos2 = sqrt(cos2);

				Vector3d v = refr * i + (refr*cos1 - cos2)*N;

				Ray ray_refr(point + (EPSILON * ray.getDirection()), v);
				ray_refr.getDirection() = ray_refr.getDirection()/norm2(ray_refr.getDirection());

				Color3d color_refr(0.);
				RayTrace(ray_refr, color_refr, level+1); //calcul du rayon refracté

				color = color + (BLFactor * color_refr);
			}
		}
	}
}

