#ifndef CG1RAYTRACER_SOLIDS_QUAD_HEADER
#define CG1RAYTRACER_SOLIDS_QUAD_HEADER

#include <rt/solids/solid.h>
#include <core\point.h>
#include <rt\ray.h>
#include <rt\intersection.h>
#include <rt/bbox.h>

namespace rt {

class Quad : public Solid {
public:
    Quad() {}
    Quad(const Point& v1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
private:
	Point qv1,qv2,qv3,qv4;
	Vector qnormal,qspan1,qspan2;
	CoordMapper* qtexMapper;
	Material* qmaterial;
};

}

#endif
