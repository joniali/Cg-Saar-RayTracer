#include <rt\integrators\raytrace.h>
#include <iostream>
using namespace std;
namespace rt 
{

	RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const
	{
	
		Intersection cint = world->scene->intersect(ray);
		Vector normal = cint.normal().normalize();
		if (cint)
		{
			
			RGBColor color = RGBColor::rep(0.0f);
			for each (Light *ls in world->light)
			{
				LightHit lh= ls->getLightHit(cint.hitPoint()); 
				float a = dot(lh.direction, cint.normal().normalize());
				float b = dot(ray.d, cint.normal().normalize());
				Vector inDir = lh.direction.normalize();
				if ((a > 0.0 && b>0.0) || (a<0.0 && b<0.0 ))
				{
					Ray sr(cint.hitPoint() , -1*lh.direction.normalize());
					
					sr.primaryRay = false;
			
					Intersection cintshadow = world->scene->intersect(sr, lh.distance - 0.0001);
					if (!cintshadow)

					{
						float cosineterm = std::abs(dot(normal, inDir));
						RGBColor intest=ls->getIntensity(lh);
						RGBColor reflectance=  cint.solid->material->getReflectance(cint.local(), cint.normal().normalize(), ray.d*-1, lh.direction.normalize());
						RGBColor emission = cint.solid->material->getEmission(cint.local(), cint.normal().normalize(), ray.d*-1);
						color = color + ((intest*reflectance*cosineterm) + emission);
						
						
					}

				}


				
			}
			CoordMapper * mapper = cint.solid->texMapper;

			if (mapper == nullptr)
			{
				mapper = rtCoorMapper;
			}
			Point textureCoords = mapper->getCoords(cint);
			return color + cint.solid->material->getEmission(textureCoords, cint.normal(), ray.d*-1);
			
			
		}
		return RGBColor::rep(0.0f);
	
	}


}