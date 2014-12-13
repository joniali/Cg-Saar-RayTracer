#ifndef CG1RAYTRACER_SOLIDS_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_SPHERE_HEADER

#include <rt/solids/solid.h>
#include <core\point.h>
#include <rt\ray.h>
#include <core\vector.h>
#include <rt\intersection.h>
#include <rt/bbox.h>

namespace rt {

class Sphere : public Solid {
public:
	Sphere() {}
	Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material);

	virtual BBox getBounds() const;
	virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
	virtual float getArea() const;
	virtual bool inside(const Point &p)const;

private:
	Point scenter;
	float sradius;
	CoordMapper* stexMapper;
	Material* smaterial;
};

}


#endif
