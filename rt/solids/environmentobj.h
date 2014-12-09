#ifndef CG1RAYTRACER_SOLIDS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_SOLIDS_ENVIRONMENT_HEADER

#include <rt/solids/solid.h>
#include <rt/ray.h>
#include <rt/intersection.h>
#include <core/point.h>
#include <string>
#include <rt/bbox.h>
#include <core/matrix.h>
#include <rt/materials/flatmaterial.h>
#include <rt/textures/imagetex.h>
#include <rt/coordmappers/environmentMapper.h>


namespace rt {

	class EnvironmentSolid : public Solid {
	public:
		EnvironmentSolid(Vector & zenith, Vector & referenceAzimuth, CoordMapper* texMapper = nullptr, Material* material = nullptr);

		virtual BBox getBounds() const;
		virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
		virtual Point sample() const;
		virtual float getArea() const;
		virtual Vector getNormalAtPoint(const Point &p) const;
		virtual float getIntersectionComplexity() const { return 1; }
		

	private:
		Point mCenter;
		float mR;

		BBox mBBox;

		CoordinateFrame mFrame;


	};

}


#endif