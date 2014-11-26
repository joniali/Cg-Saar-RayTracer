#include <rt\integrators\recraytrace.h>

namespace rt
{
	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray, int& depth) const
	{
		if (depth > 8) return RGBColor::rep(0.0f);
		Intersection cint = world->scene->intersect(ray);
		Vector normal = cint.normal().normalize();
		RGBColor color = RGBColor::rep(0.0f);

		if (cint)
		{

			if (cint.solid->material->useSampling() != Material::SAMPLING_NOT_NEEDED)
			{
				// check for material sampling
				Material::SampleReflectance sampref = cint.solid->material->getSampleReflectance(cint.local(), normal, -1 * ray.d);
				Ray secondaryRay(cint.hitPoint(), sampref.direction);
				
				color = color + getRadiance(secondaryRay, depth += 1)*(sampref.reflectance); 




				if (cint.solid->material->useSampling() == Material::SAMPLING_ALL)
					return color;
			}

			for each (Light *ls in world->light)
			{
				LightHit lh = ls->getLightHit(cint.hitPoint());
				float a = dot(lh.direction, cint.normal().normalize());
				float b = dot(ray.d, cint.normal().normalize());
				Vector inDir = lh.direction.normalize();
				if ((a > 0.0 && b > 0.0) || (a < 0.0 && b < 0.0))
				{
					Ray sr(cint.hitPoint(), -1 * lh.direction.normalize());

					sr.primaryRay = false;

					Intersection cintshadow = world->scene->intersect(sr, lh.distance - 0.0001);
					if (!cintshadow)

					{
						float cosineterm = std::abs(dot(normal, inDir));
						RGBColor intest = ls->getIntensity(lh);
						RGBColor reflectance = cint.solid->material->getReflectance(cint.local(), cint.normal().normalize(), ray.d*-1, lh.direction.normalize());
						RGBColor emission = cint.solid->material->getEmission(cint.local(), cint.normal().normalize(), ray.d*-1);
						color = color + ((intest*reflectance*cosineterm) + emission);


					}

				}



			}



		}
		return color;

	
	}
	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const
	{
		int depth = 0;
		return getRadiance(ray, depth);
	}

}