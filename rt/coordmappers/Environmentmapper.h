#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

	class Intersection;
	class EnvironmentCoordMapper : public CoordMapper {
	public:
		EnvironmentCoordMapper();
		explicit EnvironmentCoordMapper(const Float4& scale);
		EnvironmentCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef);
		virtual Point getCoords(const Intersection& hit) const;
	private:
		Float4 wScale;
	};

}

#endif
