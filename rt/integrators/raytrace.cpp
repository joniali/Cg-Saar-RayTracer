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
				float b = dot(ray.d, cint.normal().normalize());
				float c = dot(ray.d.normalize(), -1 * cint.normal().normalize());
				if ((a > 0.0 && b>0.0) || (a<0.0 &&b<0.0))
				{
					Ray sr(ls->lposition, lh.direction.normalize());
					//Ray sr(cint.hitPoint(), -lh.direction.normalize());

					
					Intersection cintshadow = world->scene->intersect(sr, lh.distance + 0.1);
					if (abs(cintshadow.hitPoint().x - cint.hitPoint().x) + abs(cintshadow.hitPoint().y - cint.hitPoint().y) + abs(cintshadow.hitPoint().z - cint.hitPoint().z) <0.0001)
					{
						
						RGBColor intest=ls->getIntensity(lh);
						RGBColor cosineterm=cint.solid->material->getReflectance(cint.local(), cint.normal().normalize(), ray.d*-1, lh.direction.normalize());
						RGBColor emission = cint.solid->material->getEmission(cint.local(), cint.normal().normalize(), ray.d*-1);
						color = color +  ((intest*cosineterm) + emission);
						
						
					}

				}


				
			}
			return color;
			
			
		}
		return RGBColor::rep(0.0f);
	
	}


}