#include <rt\lights\directional.h>

namespace rt
{


	DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
	{
		lIntensity = color;
		lDirection = direction;
	
	}
	LightHit DirectionalLight::getLightHit(const Point& p) const
	{
		LightHit *lh = new LightHit();
		lh->direction = (lDirection).normalize();
		lh->distance = FLT_MAX;
		return *lh;
	}
	RGBColor DirectionalLight::getIntensity(const LightHit& irr) const
	{
		return lIntensity;
	}
}