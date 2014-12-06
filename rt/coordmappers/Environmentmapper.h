#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <core/matrix.h>
#include <rt/intersection.h>
namespace rt {
	class Intersection;
	class EnvironmentMapper : public CoordMapper {
	public:
		EnvironmentMapper(Vector & zenith, Vector & referenceAzimuth);
		virtual Point getCoords(const Intersection& hit) const;
	private:
		Vector eLocalZenith;
		CoordinateFrame eFrame;
		Vector eLocalReferenceAzimuth;
		float eInitialPhasePhi;
	};
}
#endif 