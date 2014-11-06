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

			float numera=cint.distance-cdnearDist;
			float interp;
			
			if(numera<0)
			interp=0;
			else if(numera>cdfarDist)
			interp=1;
			else
			 interp=  numera/(cdfarDist-cdnearDist);

			float value=abs(dot(ray.d.normalize(),cint.normal().normalize()));
			//std::cout<< interp<<std::endl;
			return value*(((1-interp)* cdnearColor)+ ((interp)*cdfarColor));
			//return RGBColor(value,value,value);
		}
		return RGBColor(0,0,0);
	}
}