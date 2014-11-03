#include <rt\integrators\castingdist.h>

namespace rt{

	RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist): Integrator(world)
	{
		//world=world;
		cdnearColor=nearColor;
		this->cdnearDist=nearDist;
		cdfarColor=farColor;
		this->cdfarDist=farDist;
	}
	RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const
	{

		Intersection cint= world->scene->intersect(ray);
		
		if(cint)
		{

			float interp= cint.distance/(cdfarDist-cdnearDist);

			float value=dot(ray.d.normalize(),cint.normal().normalize());

			return value*((interp* cdnearColor)+ ((1-interp)*cdfarColor));
		}
		return RGBColor(0,0,0);
	}
}