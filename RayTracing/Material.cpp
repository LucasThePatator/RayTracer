#include "StdAfx.h"
#include "Material.h"

Material::Material(void)
{
}

Material::Material(const Color3d &color, const Color3d &reflect, double diffusion, double refractIndex, double refractAbs) 
	:color(color), reflect(reflect), diffusion(diffusion), refractIndex(refractIndex), refractAbs(refractAbs)
{

}


Material::~Material(void)
{
}
