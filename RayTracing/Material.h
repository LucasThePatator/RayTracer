#pragma once

#include "commons.h"

class Material
{
public:
	Material(void);
	Material(const Color3d &color, const Color3d &reflect, double diffusion, double refractIndex, double refractAbs);
	~Material(void);

	const Color3d &getColor() const {return color;}
	const Color3d &getReflect() const {return reflect;}
	double getRefractIndex() const {return refractIndex;}
	double getRefractAbs() const {return refractAbs;}
	double getDiffusion() const {return diffusion;}

private :

	Color3d color;
	Color3d reflect;
	double diffusion;
	double refractIndex;
	double refractAbs;
};

