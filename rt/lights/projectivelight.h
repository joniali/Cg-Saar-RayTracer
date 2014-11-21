#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <rt/lights/light.h>
#include <core/point.h>
#include <core/color.h>


namespace rt {

	class ProjectiveLight : public Light {
	public:
		ProjectiveLight() {}
		ProjectiveLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity);
		virtual LightHit getLightHit(const Point& p) const;
		virtual RGBColor getIntensity(const LightHit& irr) const;

	private:
		float pangle, pexp;

	};


}

#endif

