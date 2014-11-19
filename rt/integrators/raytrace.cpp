#include <rt\integrators\raytrace.h>

namespace rt 
{

	RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const
	{
	
		Intersection cint = world->scene->intersect(ray);

		if (cint)
		{
			//float value = abs(dot(ray.d.normalize(), cint.normal().normalize()));

			for each (Light *ls in world->light)
			{
				LightHit lh= ls->getLightHit(cint.hitPoint());
				if (dot(lh.direction, cint.normal()) > 0)
				{
					Ray sr(ls->lposition, lh.direction*-1);
					
					Intersection cintshadow = world->scene->intersect(sr);
					if (cintshadow == cint)
					{
						
						RGBColor intest=ls->getIntensity(lh);
						RGBColor cosineterm=cint.solid->material->getReflectance(cint.local(), cint.normal(), ray.d*-1, lh.direction);
						RGBColor emission = cint.solid->material->getEmission(cint.local(), cint.normal(), ray.d*-1);
						return ((intest*cosineterm) + emission);
						
						
					}

				}


				
			}
			
		}
		return RGBColor::rep(0.0f);
	
	}


}