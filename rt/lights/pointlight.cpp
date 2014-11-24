#include <rt\lights\pointlight.h>


namespace rt 

{
	PointLight::PointLight(const Point& position, const RGBColor& intensity)
	{
	
		pposition = position;
		pIntensity = intensity;
	}
	LightHit PointLight::getLightHit(const Point& p) const
	{
		LightHit *lh = new LightHit();
		lh->direction = (p -pposition).normalize();
		lh->distance = (p - pposition).length();
		return *lh;
	
	}

	RGBColor PointLight::getIntensity(const LightHit& irr) const
	{
		
		
		return pIntensity / float (irr.distance*irr.distance);
		
	
	}



}