#pragma once

#include "commons.h"

class Material
{
public:
	Material(void);
	~Material(void);

	const Color3d &getColor() const {return color;}
	const Color3d &getReflect() const {return reflect;}
	double getRefractIndex() const {return refractIndex;}
	double getRefractAbs() const {return refractAbs;}

private :

	Color3d color;
	Color3d reflect;
	double refractIndex;
	double refractAbs;
};

