#ifndef CG1RAYTRACER_COORDMAPPERS_PLANE_HEADER
#define CG1RAYTRACER_COORDMAPPERS_PLANE_HEADER

#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt\intersection.h>
#include <core\Matrix.h>

namespace rt {

class Intersection;

class PlaneCoordMapper : public CoordMapper{
public:
    PlaneCoordMapper(const Vector& e1, const Vector& e2);
    virtual Point getCoords(const Intersection& hit) const;
private:
	Vector pe1, pe2,pnormal;
	Matrix transition;

};

}

#endif
