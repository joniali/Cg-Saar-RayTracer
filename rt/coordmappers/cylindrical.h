#ifndef CG1RAYTRACER_COORDMAPPERS_CYLINDRICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_CYLINDRICAL_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <core/Matrix.h>
#include <rt\intersection.h>
namespace rt {

class Intersection;

class CylindricalCoordMapper : public CoordMapper {
public:
    CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis);
    virtual Point getCoords(const Intersection& hit) const;
private:
	Point cOrigin;
	CoordinateFrame cFrame;
	Vector cLocalL;
	Vector cLocalA;
	float cXScale;
	float cYScale;
};

}

#endif
