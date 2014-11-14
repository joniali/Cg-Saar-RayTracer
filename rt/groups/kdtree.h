#ifndef CG1RAYTRACER_GROUPS_KDTREE_HEADER
#define CG1RAYTRACER_GROUPS_KDTREE_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <iostream>
#include <stack>
using namespace std;
namespace rt {
	class KDNode;
class KDTree : public Group {
public:
	KDTree(){}
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
	virtual ~KDTree();
    virtual void add(Primitive* p);
	virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
private: 
	std::vector< Primitive * > kPrimitives;
	BBox kBBox;
	KDNode * rootNode;


};

}

#endif
