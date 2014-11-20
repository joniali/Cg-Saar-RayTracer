#include <rt\lights\spotlight.h>


namespace rt

{
	SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity)
	{

		lposition = position;
		lIntensity = intensity;
		lAngle = angle;
		lDirection = direction;
		lExp = exp;
	}
	LightHit SpotLight::getLightHit(const Point& p) const
	{
		LightHit *lh = new LightHit();
		lh->direction = (p - lposition).normalize();
		lh->distance = (p - lposition).length();
		return *lh;

	}

	RGBColor SpotLight::getIntensity(const LightHit& irr) const
	{

		//if (irr.distance != 0);
		return lIntensity / float (irr.distance*irr.distance);
		//return RGBColor::rep(1.0f);

	}



}