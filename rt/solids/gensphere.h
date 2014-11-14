#ifndef CG1RAYTRACER_SOLIDS_GENERAL_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_GENERAL_SPHERE_HEADER

#include <rt\solids\generalquadric.h>
#include <rt/solids/solid.h>
#include <core\point.h>
#include <rt\ray.h>
#include <core\vector.h>
#include <rt\intersection.h>
#include <rt/bbox.h>


namespace rt{


class GenSphere : public GeneralQuadric {
public:
GenSphere() {}
GenSphere(const Point& center, float radius, CoordMapper* texMapper, Material* material);
virtual BBox getBounds() const;
private:
Point gscenter;
float gsradius;
};
} 



#endif