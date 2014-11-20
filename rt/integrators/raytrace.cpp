#include <rt\integrators\raytrace.h>

namespace rt 
{

	RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const
	{
	
		Intersection cint = world->scene->intersect(ray);

		if (cint)
		{
			
			RGBColor color = RGBColor::rep(0.0f);
			for each (Light *ls in world->light)
			{
				LightHit lh= ls->getLightHit(cint.hitPoint()); 
				float a = dot(lh.direction, cint.normal().normalize());
				//float b = dot(ray.d, cint.normal().normalize());
				if ( (a > 0.0 ))//&& b>0.0 ) || (a<0.0 &&b<0.0))
				{
					Ray sr(ls->lposition, lh.direction.normalize());
					
					Intersection cintshadow = world->scene->intersect(sr);
					if (cintshadow.distance < lh.distance + 0.000001)
					{
						
						RGBColor intest=ls->getIntensity(lh);
						RGBColor cosineterm=cint.solid->material->getReflectance(cint.local(), cint.normal().normalize(), ray.d*-1, lh.direction.normalize());
						RGBColor emission = cint.solid->material->getEmission(cint.local(), cint.normal(), ray.d*-1);
						color = color +  ((intest*cosineterm) + emission);
						
						
					}

				}


				
			}
			return color;
			
			
		}
		return RGBColor::rep(0.0f);
	
	}


}