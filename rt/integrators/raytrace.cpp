#include <rt\integrators\raytrace.h>

namespace rt 
{

	RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const
	{
	
		Intersection cint = world->scene->intersect(ray);

		if (cint)
		{
			

			for each (Light *ls in world->light)
			{
				LightHit lh= ls->getLightHit(cint.hitPoint()); // remove extra tracing
				if (dot(lh.direction, cint.normal()) >= 0.0)
				{
					Ray sr(ls->lposition, lh.direction);
					
					Intersection cintshadow = world->scene->intersect(sr);
					if (cintshadow.hitPoint()==cint.hitPoint())
					{
						
						RGBColor intest=ls->getIntensity(lh);
						RGBColor cosineterm=cint.solid->material->getReflectance(cint.local(), cint.normal(), ray.d*-1, lh.direction);
						RGBColor emission = cint.solid->material->getEmission(cint.local(), cint.normal(), ray.d*-1);
						return  ((intest*cosineterm) + emission);
						
						
					}

				}


				
			}
			
			
		}
		return RGBColor::rep(0.0f);
	
	}


}