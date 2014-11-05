#include <rt/integrators/casting.h>


namespace rt {

	RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const
	{
		Intersection cint= world->scene->intersect(ray);
		
		if(cint)
		{
			float value=abs(dot(ray.d.normalize(),cint.normal().normalize()));

				return RGBColor(value,value,value);
		}
		return RGBColor(0,0,0);
	}

}