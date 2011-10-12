// RayTracing.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "commons.h"
#include "Sphere.h"
#include "InfinitePlan.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Material.h"

#include "Light.h"

#include <iostream>
#include <SDL.h>

#include <stdint.h>

void drawPixel(SDL_Surface *SDLScreen, Color3d &color, int i, int j) {

	if ( SDL_MUSTLOCK(SDLScreen) ) {
        if ( SDL_LockSurface(SDLScreen) < 0 ) {
            return;
        }
    }

	Uint32 *bufp;
	Uint32 SDLColor = SDL_MapRGB(SDLScreen->format, (Uint8)((color[0] > 1 ? 1 : color[0])*UINT8_MAX), (Uint8)((color[1] > 1 ? 1 : color[1])*UINT8_MAX), (Uint8)((color[2] > 1 ? 1 : color[2])*UINT8_MAX));
	if (color[1] != 0)
		int bite = 0;

	bufp = (Uint32 *)SDLScreen->pixels + j*SDLScreen->pitch/4 + i;
	*bufp = SDLColor;

	if ( SDL_MUSTLOCK(SDLScreen) ) {
        SDL_UnlockSurface(SDLScreen);
    }
    SDL_UpdateRect(SDLScreen, i, j, 1, 1);
}

int _tmain(int argc, _TCHAR* argv[])
{

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Impossible d'initialiser SDL: %s\n", SDL_GetError());
        exit(1);
    }

	SDL_Surface *SDLScreen;

    SDLScreen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if ( SDLScreen == NULL ) {
        fprintf(stderr, "Impossible de passer en 640x480 en 16 bpp: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

	Color3d *screen = new Color3d[800*600];
	RayTracer rt(0.001, 0.001, 800, 600, 1);
	
	//Description de la scene
	SimpleScene scene;

	//sphere verte
	Point3d center1;
	center1[0] = 5;
	center1[1] = 0;
	center1[2] = -.5;
	double radius = 0.3;
	Sphere s1(center1, radius);
	Color3d reflect1(0.5);
	Color3d color1(0);
	color1[1] = 1;
	Material mat1(color1, reflect1, 0.5, 1.5, LARGE_DOUBLE);
	s1.setMaterial(mat1);
	scene.addPrimitive(s1);
	
	//Sphere rouge
	Point3d center2;
	center2[0] = 10 + 0.5;
	center2[1] = 0;
	center2[2] = 0.5;
	Sphere s2(center2, 0.5);

	Color3d color2(0);
	Color3d reflect2(0.5);
	color2[0] = 1;
	Material mat2(color2, reflect2, 0.5, 1.5, LARGE_DOUBLE);
	s2.setMaterial(mat2);
	scene.addPrimitive(s2);

	//Sphere bleue
	Point3d center3;
	center3[0] = 4 + .5;
	center3[1] = 0.7;
	center3[2] = 0;
	Sphere s3(center3, 0.25);

	Color3d color3(0);
	color3[2] = 1;
	Color3d reflect3(0);
	Material mat3(color3, reflect3, 0.5, 1.5, LARGE_DOUBLE);
	s3.setMaterial(mat3);
	scene.addPrimitive(s3);

	//Sphere blanche
	Point3d center4;
	center4[0] = 7;
	center4[1] = -2;
	center4[2] = 0;
	
	Sphere s4(center4, 0.2);

	Color3d color4(0);
	Color3d reflect4(1);
	color4[2] = 0;
	Material mat4(color4, reflect4, 0, 1.5, 5);
	s4.setMaterial(mat4);
	scene.addPrimitive(s4);


	////Plan blanc
	/*Vector3d normal1(0);
	normal1[0] = -1;*/
	Color3d white(1);
	Color3d reflectPlan1(1);
	Material matPlan1(white, reflectPlan1, 1, 1, 0); 
	//Point3d pt1(0);
	//pt1[0] = 20;
	//pt1[1] = 0;
	//pt1[2] = 0;

	/*InfinitePlan plan1(normal1, pt1);
	plan1.setMaterial(matPlan1);*/
	/*scene.addPrimitive(plan1);*/

	Vector3d normal2(0);
	normal2[2] = 1;
	Point3d pt2(0);
	pt2[0] = 0;
	pt2[1] = 0;
	pt2[2] = -1;

	InfinitePlan plan2(normal2, pt2);
	plan2.setMaterial(matPlan1);
	scene.addPrimitive(plan2);
	
	Point3d origin;
	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;

	Point3d lightPosition1(0);
	Point3d lightPosition2(0);
	Color3d lightColor(1);
	
	lightPosition1[0] = 3;
	lightPosition1[1] = -3;
	lightPosition1[2] = 5;

	lightPosition2[2] = -1;
	lightPosition2[1] = 1;

	Light light1(lightPosition1, lightColor);
	scene.addLight(light1);

	Light light2(lightPosition2, lightColor);
	scene.addLight(light2);
	
	rt.setScene(&scene);
	rt.draw(screen);

	for (int i = 0; i < 800; i++) 
	{
		for (int j = 0; j < 600; j++) 
		{
			drawPixel(SDLScreen, screen[i+j*800], i, j);
		}
	}

	SDL_Event event;

	SDL_WaitEvent(&event);
	bool continuer = true;
	while(continuer) 
	{
		SDL_WaitEvent(&event);
		if(event.key.keysym.sym == SDLK_ESCAPE)
			continuer = false;
	}

	return 0;
}



