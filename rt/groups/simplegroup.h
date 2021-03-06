#ifndef CG1RAYTRACER_GROUPS_SIMPLEGROUP_HEADER
#define CG1RAYTRACER_GROUPS_SIMPLEGROUP_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt\primitive.h>
#include <rt\bbox.h>
#include <rt\intersection.h>
#include <iostream>
using namespace std;
namespace rt {

class SimpleGroup : public Group {
public:
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);

private:
	vector<Primitive *> sgPrimitives;
	CoordMapper* sgcm;
	Material* sgm;
	BBox sgbbox;
};


}

#endif
