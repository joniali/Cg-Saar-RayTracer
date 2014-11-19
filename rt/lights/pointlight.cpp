#include <rt\lights\pointlight.h>


namespace rt 

{
	PointLight::PointLight(const Point& position, const RGBColor& intensity)
	{
	
		lposition = position;
		lIntensity = intensity;
	}
	LightHit PointLight::getLightHit(const Point& p) const
	{
		LightHit *lh = new LightHit();
		lh->direction = (lposition - p).normalize();
		lh->distance = (p - lposition).length();
		return *lh;
	
	}

	RGBColor PointLight::getIntensity(const LightHit& irr) const
	{
		
		return lIntensity / (irr.distance*irr.distance);
	
	}



}