#ifndef CG1RAYTRACER_PRIMITIVE_HEADER
#define CG1RAYTRACER_PRIMITIVE_HEADER

#include<core/scalar.h>
#include<core/vector.h>
#include<vector>

namespace rt {

class BBox;
class Ray;
class Intersection;
class Material;
class CoordMapper;

/*
Primitive represents any object in the virtual scene that can be intersected by a ray.
It may be as simple as a plane or triangle, but more complex objects can be primitives as well
*/
class Primitive {
public:
    virtual BBox getBounds() const = 0;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const = 0;
    virtual void setMaterial(Material* m) = 0;
    virtual void setCoordMapper(CoordMapper* cm) = 0;
};
/* Inherited by:

- Solid (solid.h)
- Group (group.h)
*/

}

#endif
