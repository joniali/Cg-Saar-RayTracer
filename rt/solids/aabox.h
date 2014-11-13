#ifndef CG1RAYTRACER_SOLIDS_BOX_HEADER
#define CG1RAYTRACER_SOLIDS_BOX_HEADER

#include <rt/solids/solid.h>
#include <core\point.h>
#include <rt\intersection.h>
#include <rt/bbox.h>

namespace rt {

class AABox : public Solid {
public:
    AABox() {}
    AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual Point sample() const;
    virtual float getArea() const;
	Vector normal(const int face_hit) const;

private: 
	Point aacorner1,aacorner2;
	CoordMapper* aatexMapper;
	Material* aamaterial;
};

}

#endif
