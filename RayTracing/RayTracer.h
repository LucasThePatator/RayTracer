#pragma once

#include "SimpleScene.h"
#include "commons.h"

class RayTracer
{
public:
	
	RayTracer(double pixelWidth, double pixelHeight, int width, int height, double depth);
	~RayTracer(void);

	void draw(Color3d* screen) const;
    void setViewer(double width, double height, const Vector3d& origin, const Vector3d& direction);
	void setScene(SimpleScene *scene);
	void setResolution(int pixelWidth, int pixelHeight);


private :
	void generateRay(int x, int y, Ray& ray) const;
	void RayTrace(const Ray& ray, Color3d& color, unsigned int level) const;

	SimpleScene *scene;
	double pixelWidth, pixelHeight, focale; //Taille des pixels en unité de mesure et distance focale
	int width, height; //Taille de l'écran

	Point3d origin;
    Vector3d direction;
};

