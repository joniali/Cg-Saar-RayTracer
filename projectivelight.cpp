#include <rt\lights\projectivelight.h>

namespace rt

{

	ProjectiveLight::ProjectiveLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity)
	{

		lDirection = direction.normalize();
		lposition = position;
		sangle = angle;
		sexp = exp;
		lIntensity = intensity;
	}
	LightHit ProjectiveLight::getLightHit(const Point& p) const
	{
		LightHit *lh = new LightHit();
		lh->direction = (p - lposition).normalize();
		lh->distance = (p - lposition).length();
		return *lh;
	}
	RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const
	{
		//check if it lies outside the angle
		float angle = abs(acos(dot(irr.direction.normalize(), lDirection)));
		if (angle <= sangle)
			return lIntensity* (pow(abs(dot(irr.direction.normalize(), lDirection.normalize())), sexp)) / float(irr.distance*irr.distance);

		return RGBColor::rep(0.0);

	}

}