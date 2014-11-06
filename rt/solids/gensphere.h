#ifndef CG1RAYTRACER_SOLIDS_GENERAL_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_GENERAL_SPHERE_HEADER

#include <rt\solids\generalquadric.h>


namespace rt{


class GenSphere : public GeneralQuadric {
public:
GenSphere() {}
GenSphere(const Point& center, float radius, CoordMapper* texMapper, Material* material);

private:
Point gscenter;
float gsradius;
};
} 



#endif