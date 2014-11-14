#ifndef CG1RAYTRACER_SOLIDS_GENERAL_QUADRIC_HEADER
#define CG1RAYTRACER_SOLIDS_GENERAL_QUADRIC_HEADER
#include <rt/solids/solid.h>
#include <core/point.h>
#include <core/vector.h>
#include <rt\intersection.h>
#include <rt/bbox.h>
namespace rt {
class Material;
class CoordMapper;
class GeneralQuadric : public Solid {
public:
Material* material;
CoordMapper* texMapper;
GeneralQuadric() {}
explicit GeneralQuadric(float params[10], CoordMapper* texMapper = nullptr, Material* material = nullptr);
//virtual BBox getBounds() const;
virtual Point sample() const;
virtual float getArea() const;
virtual Vector getNormal(Point& p) const;
virtual void setMaterial(Material* m) { material = m; }
virtual void setCoordMapper(CoordMapper* cm) { texMapper = cm; }
virtual BBox getBounds() const;
virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
// parametrs of the general quadric
protected:
float a, b, c, d, e, f, g, h, i, j;
};
}
#endif 